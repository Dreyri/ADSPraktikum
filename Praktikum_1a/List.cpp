#include "List.h"
List::List()
{
	head = new Node;
	tail = new Node;
	_size = 0;
	head->next = tail;
	tail->prev = head;
}
List::~List()
{
    /*
	( ... löschen Sie alle noch vorhandenen Knoten Node dieser Instanz 
		Denken Sie auch den die Knoten head und tail.)
    */
    
    Node* curNode = head;
    while(curNode != tail)
    {
        //delete all nodes until we hit tail
        Node* nextNode = curNode->next;

        delete curNode;

        curNode = nextNode;
    }

    //make sure we delete tail as well
    delete tail;
}
void List::InsertFront(int key)
{
    //head and tail hold no values I assume
    
	//( ... Erweitern Sie die Methode so, dass ein neuer Knoten Node vorne
		//(hinter dem Knoten head) in die Liste eingefügt wird. )
    
    //store previously first one
    Node* prevFirst = head->next;

    //create new node and set as first
    Node* n = new Node(key, prevFirst, head);
    head->next = n;
    
    //adjust prevFirst to recognize n as the first
    prevFirst->prev = n;

    ++_size;
}
void List::InsertBack(int key)
{
    /*
	( ... Erweitern Sie die Methode so, dass ein neuer Knoten Node hinten
		(vor dem Knoten tail) in die Liste eingefügt wird. )
    */
    //again save the last node
    Node* prevLast = tail->prev;

    Node* n = new Node(key, tail, prevLast);
    tail->prev = n;

    //make it see its new master
    prevLast->next = n;

    ++_size;
}
bool List::getFront(int & key)
{
    /*
	( ... Erweitern Sie die Methode so, dass der erste Knoten der Liste
		(hinter head) zurückgegeben und dieser Knoten dann gelöscht wird.
		Im Erfolgsfall geben Sie true zurück, sonst false. )
    */

    //no point if we have no nodes
    if(_size == 0)
        return false;

    //the one we want
    Node* ourNode = head->next;

    //assign the value
    key = ourNode->key;

    //our new first node
    Node* newNext = ourNode->next;

    //link our nodes together
    head->next = newNext;
    newNext->prev = head;
    
    //no memory leaks pls
    delete ourNode;
    --_size;

    return true;
}
bool List::getBack(int & key)
{
    /*
	(... Erweitern Sie die Methode so, dass der letzte Knoten der Liste
		(vor tail) zurückgegeben und dieser Knoten dann gelöscht wird.
		Im Erfolgsfall geben Sie true zurück, sonst false. )
    */

    if(_size == 0)
        return false;

    //same as function above pretty much
    Node* ourNode = tail->prev;

    key = ourNode->key;

    Node* newPrev = ourNode->prev;

    tail->prev = newPrev;
    newPrev->next = tail;

    delete ourNode;
    --_size;

    return true;
}
bool List::del(int key)
{
    /*
	(... Die Methode del sucht den Knoten mit dem Wert Key und löscht diesen
		im Erfolgsfall aus der Liste.
		Im Erfolgsfall geben Sie true zurück, sonst false. )
    */
    Node* curNode = head;

    for(int i = 0; i < _size; ++i)
    {
        curNode = curNode->next;
        if(curNode->key == key)
        {
            //time to delete and relink
            Node* prevNode = curNode->prev;
            Node* nextNode = curNode->next;

            prevNode->next = nextNode;
            nextNode->prev = prevNode;

            delete curNode;
            --_size;
            return true;
        }

    }
    return false;
}
bool List::search(int key)
{
    /*
	(... Die Methode search sucht den Knoten mit dem Wert key
		Im Erfolgsfall geben Sie true zurück, sonst false. )
    */

    Node* curNode = head;

    //just same as our above for loop
    for(int i = 0; i < _size; ++i)
    {
        curNode = curNode->next;
        if(curNode->key == key)
        {
            //nothing more to be done here
            return true;
        }
    }

    return false;
}
bool List::swap(int key1, int key2)
{
    /*
	(... Die Methode swap sucht den Knoten mit dem Wert key1,
		dann den Knoten mit dem Wert key2. Diese Knoten werden dann
		getauscht, indem die Zeiger der Knoten entsprechend geändert
		werden. )
    */

    Node* curNode = head;
    Node* node1 = nullptr;
    Node* node2 = nullptr;

    for(int i = 0; i < _size; ++i)
    {
        curNode = curNode->next;
        if(curNode->key == key1)
        {
            //found our first target
            node1 = curNode;
            break;
        }
    }

    curNode = head;

    for(int i = 0; i < _size; ++i)
    {
        curNode = curNode->next;
        if(curNode->key == key2)
        {
            //found second target
            node2 = curNode;
            break;
        }
    }

    //one of the 2 couldn't be found
    if((node1 == nullptr) || (node2 == nullptr))
        return false;

    Node* prevNode1 = node1->prev;
    Node* prevNode2 = node2->prev;

    Node* nextNode1 = node1->next;
    Node* nextNode2 = node2->next;

    //swap things for node2
    prevNode1->next = node2;
    node2->prev = prevNode1;
    nextNode1->prev = node2;
    node2->next = nextNode1;

    //swap things for node1 just changed numbers from first one
    //hope it works
    prevNode2->next = node1;
    node1->prev = prevNode2;
    nextNode2->prev = node1;
    node1->next = nextNode2;

    return true;
}
int List::size(void)
{
	//(... Die Methode git den Wert von size (Anzahl der Knoten in der Liste) zurück. )
    return _size;

}
bool List::test(void)
{
    /*
	(... Die Methode überprüft die Pointer der Liste. Gestartet wird mit head. Es werden alle 
		Knoten bis zum tail durchlaufen von dort aus dann die prev-Zeiger bis zum head.
		Bei Erfolg wird true zurück gegeben. )
    */
    Node* prev = nullptr;
    Node* cur = head;
    Node* next = head->next;

    for(int i = 0; i < _size; ++i)
    {
        //update to current position
        prev = cur;
        cur = next;
        next = cur->next;

        //check pointer correctness
        if(prev->next != cur)
            return false;
        if(cur->prev != prev)
            return false;
        if(next->prev != cur)
            return false;
        if(cur->next != next)
            return false;

    }
    //all good we made it
    return true;
}
void List::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	// Setzen der Formatierung für den überladenen Streamingoperator <<
	_form.start = start;			// Ausgabe zu Beginn der Liste
	_form.zwischen = zwischen;		// Ausgabe zwischen zwei Knoten
	_form.ende = ende;				// Ausgabe am Ende der Liste
}
List & List::operator = (const List & _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == & _List) return *this;	//  !! keine Aktion notwendig
	Node * tmp_node;
	if (_size)
	{
		Node * tmp_del;
		tmp_node = head->next;
		while (tmp_node != tail)		// Alle eventuell vorhandenen Knoten in this löschen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		_size = 0;
		head->next = tail;
		tail->prev = head;
	}
	tmp_node = _List.head->next;
	while (tmp_node != _List.tail)
	{
		InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	return *this;
}
List & List::operator = (const List * _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;	//  !! keine Aktion notwendig
	Node * tmp_node;
	if (_size)
	{	
		Node * tmp_del;
		tmp_node = head->next;
		while (tmp_node != tail)		// Alle eventuell vorhandenen Knoten in this löschen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		_size = 0;
		head->next = tail;
		tail->prev = head;
	}
	tmp_node = _List->head->next;
	while (tmp_node != _List->tail)
	{
		InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	return * this;
}
List & List::operator + (const List & List_Append) const
{
	List * tmp = new List;
	Node * tmp_node;
	tmp_node = head->next;
	while (tmp_node != tail){
		tmp->InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (!List_Append._size) return * tmp;
	tmp_node = List_Append.head->next;
	while (tmp_node != List_Append.tail){
		tmp->InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	return * tmp;
}
List & List::operator + (const List * List_Append) const
{
	List * tmp = new List;
	Node * tmp_node;
	tmp_node = head->next;
	while (tmp_node != tail){
		tmp->InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (!List_Append->_size) return *tmp;
	tmp_node = List_Append->head->next;
	while (tmp_node != List_Append->tail){
		tmp->InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	return *tmp;
}
std::ostream & operator<<(std::ostream  & stream, List const & Liste)
{
	stream << Liste._form.start;
	for (Node * tmp = Liste.head->next; tmp != Liste.tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.tail ? Liste._form.ende : Liste._form.zwischen);
	return stream;
}
std::ostream & operator << (std::ostream & stream, List const * Liste)
{
	stream << Liste->_form.start;
	for (Node * tmp = Liste->head->next; tmp != Liste->tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->tail ? Liste->_form.ende : Liste->_form.zwischen);
	return stream;
}
