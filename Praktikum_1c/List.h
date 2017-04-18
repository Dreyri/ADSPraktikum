#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <string>
#include <iostream>

template<typename T>
class List 
{
/* 
	Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse List
	kann ein Stapel oder Warteschlange realisiert werden.
*/
private:
	struct form { std::string start = "<< "; std::string zwischen = ", "; std::string ende = " >>\n"; } _form;
    Node<T>* head, * tail;
	int _size;
public:
    List()
    {
        head = new Node<T>;
        tail = new Node<T>;
        _size = 0;
        head->next = tail;
        tail->prev = head;
    }

//	List(List & _List);				// Copy Operator überladen
    ~List()
    {
        /*
        ( ... löschen Sie alle noch vorhandenen Knoten Node dieser Instanz
            Denken Sie auch den die Knoten head und tail.)
        */

        Node<T>* curNode = head;
        while(curNode != tail)
        {
            //delete all nodes until we hit tail
            Node<T>* nextNode = curNode->next;

            delete curNode;

            curNode = nextNode;
        }

        //make sure we delete tail as well
        delete tail;
    }

    void InsertFront(T key)		// Einfügen eines Knotens am Anfang
    {
        //head and tail hold no values I assume

        //( ... Erweitern Sie die Methode so, dass ein neuer Knoten Node vorne
            //(hinter dem Knoten head) in die Liste eingefügt wird. )

        //store previously first one
        Node<T>* prevFirst = head->next;

        //create new node and set as first
        Node<T>* n = new Node<T>(key, prevFirst, head);
        head->next = n;

        //adjust prevFirst to recognize n as the first
        prevFirst->prev = n;

        ++_size;
    }

    void InsertBack(T key)		// Einfügen eines Knotesn am Ende
    {
        /*
        ( ... Erweitern Sie die Methode so, dass ein neuer Knoten Node hinten
            (vor dem Knoten tail) in die Liste eingefügt wird. )
        */
        //again save the last node
        Node<T>* prevLast = tail->prev;

        Node<T>* n = new Node<T>(key, tail, prevLast);
        tail->prev = n;

        //make it see its new master
        prevLast->next = n;

        ++_size;
    }

    bool getFront(T & key)	// Entnehmen eines Knoten am Anfang
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
        Node<T>* ourNode = head->next;

        //assign the value
        key = ourNode->key;

        //our new first node
        Node<T>* newNext = ourNode->next;

        //link our nodes together
        head->next = newNext;
        newNext->prev = head;

        //no memory leaks pls
        delete ourNode;
        --_size;

        return true;
    }

    bool getBack(T & key)	// Entnehmen eines Knoten am Ende
    {
        /*
        (... Erweitern Sie die Methode so, dass der letzte Knoten der Liste
            (vor tail) zurückgegeben und dieser Knoten dann gelöscht wird.
            Im Erfolgsfall geben Sie true zurück, sonst false. )
        */

        if(_size == 0)
            return false;

        //same as function above pretty much
        Node<T>* ourNode = tail->prev;

        key = ourNode->key;

        Node<T>* newPrev = ourNode->prev;

        tail->prev = newPrev;
        newPrev->next = tail;

        delete ourNode;
        --_size;

        return true;
    }

    bool del(T key)			// löschen eines Knotens [key]
    {
        /*
        (... Die Methode del sucht den Knoten mit dem Wert Key und löscht diesen
            im Erfolgsfall aus der Liste.
            Im Erfolgsfall geben Sie true zurück, sonst false. )
        */
        Node<T>* curNode = head;

        for(int i = 0; i < _size; ++i)
        {
            curNode = curNode->next;
            if(curNode->key == key)
            {
                //time to delete and relink
                Node<T>* prevNode = curNode->prev;
                Node<T>* nextNode = curNode->next;

                prevNode->next = nextNode;
                nextNode->prev = prevNode;

                delete curNode;
                --_size;
                return true;
            }

        }
        return false;
    }

    bool search(T key)		// Suchen eines Knoten
    {
        /*
        (... Die Methode search sucht den Knoten mit dem Wert key
            Im Erfolgsfall geben Sie true zurück, sonst false. )
        */

        Node<T>* curNode = head;

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

    bool swap(T key1, T key2)	// Knoten in der Liste vertauschen
    {
        /*
        (... Die Methode swap sucht den Knoten mit dem Wert key1,
            dann den Knoten mit dem Wert key2. Diese Knoten werden dann
            getauscht, indem die Zeiger der Knoten entsprechend geändert
            werden. )
        */

        Node<T>* curNode = head;
        Node<T>* node1 = nullptr;
        Node<T>* node2 = nullptr;

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

        Node<T>* prevNode1 = node1->prev;
        Node<T>* prevNode2 = node2->prev;

        Node<T>* nextNode1 = node1->next;
        Node<T>* nextNode2 = node2->next;

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

    int size(void) { return _size; }					// Größe der Lise (Anzahl der Knoten)
    bool test(void)				// Überprüfen der Zeigerstruktur der Liste
    {
        /*
        (... Die Methode überprüft die Pointer der Liste. Gestartet wird mit head. Es werden alle
            Knoten bis zum tail durchlaufen von dort aus dann die prev-Zeiger bis zum head.
            Bei Erfolg wird true zurück gegeben. )
        */
        Node<T>* prev = nullptr;
        Node<T>* cur = head;
        Node<T>* next = head->next;

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

    void format(const std::string & start, const std::string & zwischen, const std::string & ende)	// Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
    {
        // Setzen der Formatierung für den überladenen Streamingoperator <<
        _form.start = start;			// Ausgabe zu Beginn der Liste
        _form.zwischen = zwischen;		// Ausgabe zwischen zwei Knoten
        _form.ende = ende;				// Ausgabe am Ende der Liste
    }

    List<T> & operator = (const List<T> & _List)						// Zuweisungsoperator definieren
    {
        // in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
        // Kopiert wird in das Objekt "this"
        if (this == & _List) return *this;	//  !! keine Aktion notwendig
        Node<T> * tmp_node;
        if (_size)
        {
            Node<T> * tmp_del;
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

    List<T> & operator = (const List<T> * _List)						// Zuweisungsoperator definieren
    {
        // in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
        // Kopiert wird in das Objekt "this"
        if (this == _List) return *this;	//  !! keine Aktion notwendig
        Node<T> * tmp_node;
        if (_size)
        {
            Node<T> * tmp_del;
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

    List<T> & operator + (const List<T> & List_Append) const			// Listen zusammenführen zu einer Liste
    {
        List<T> * tmp = new List;
        Node<T> * tmp_node;
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
    List<T> & operator + (const List<T> * List_Append) const			// Listen zusammenführen zu einer Liste
    {
        List<T> * tmp = new List;
        Node<T> * tmp_node;
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
    friend std::ostream & operator << (std::ostream & stream, List<T> const & Liste)		// Ausgabeoperator überladen
    {
        stream << Liste._form.start;
        for (Node<T> * tmp = Liste.head->next; tmp != Liste.tail; tmp = tmp->next)
            stream << tmp->key << (tmp->next == Liste.tail ? Liste._form.ende : Liste._form.zwischen);
        return stream;
    }

    friend std::ostream & operator << (std::ostream & stream, List<T> const * Liste)		// Ausgabeoperator überladen
    {
        stream << Liste->_form.start;
        for (Node<T> * tmp = Liste->head->next; tmp != Liste->tail; tmp = tmp->next)
            stream << tmp->key << (tmp->next == Liste->tail ? Liste->_form.ende : Liste->_form.zwischen);
        return stream;
    }
};

#endif
