#include "tree.h"

#include <functional>

Tree::Tree()
    : mAnchor(nullptr), mNextId(0)
{
}

Tree::~Tree()
{
    auto lambdaDelete = [&](TreeNode* node)
    {
        delete node;
        --mNextId;
    };

    traverse(lambdaDelete);
}

void Tree::insertNode(const std::string& name, int age, double income, int plz)
{
    TreeNode* newNode = new TreeNode(mNextId, name, age, income, plz);

    mAnchor = insertNode(mAnchor, newNode);

    ++mNextId;
}

bool Tree::deleteNode(int nodePosId)
{
    bool success = false;

    auto findMin = [](TreeNode* node) -> TreeNode*
    {
        while(node->mLeft != nullptr) node = node->mLeft;

        return node;
    };

    std::function<TreeNode*(TreeNode*, int)> nodeDelete = [&](TreeNode* node, int nodePosId) -> TreeNode*
    {
        if(node == nullptr) return node;

        else if(nodePosId < node->getNodePosId()) node->mLeft = nodeDelete(node->mLeft, nodePosId);
        else if(nodePosId > node->getNodePosId()) node->mRight = nodeDelete(node->mRight, nodePosId);
        else //found it
        {
            //case, no child
            if(node->mLeft == nullptr && node->mRight == nullptr)
            {
                success = true;
                delete node;
                node = nullptr;
            }
            else if(node->mLeft == nullptr) //case, 1 child
            {
                TreeNode* tmp = node;
                node = node->mRight;
                success = true;
                delete tmp;
            }
            else if(node->mRight == nullptr)
            {
                TreeNode* tmp = node;
                node = node->mLeft;
                success = true;
                delete tmp;
            }
            else
            {
                TreeNode* tmp = findMin(node->mRight);
                //only replace values
                node->setAge(tmp->getAge());
                node->setIncome(tmp->getIncome());
                node->setPLZ(tmp->getPLZ());
                node->setName(tmp->getName());
                //we have 2 same value nodes now, delete the one in this subtree
                node->mRight = nodeDelete(node->mRight, tmp->getNodePosId());
            }
        }
        return node;
    };

    nodeDelete(mAnchor, nodePosId);

    return success;
}

std::vector<TreeNode*> Tree::search(const std::string& name)
{
    std::vector<TreeNode*> res;
    auto searchFunc = [&](TreeNode* node)
    {
        if(node->getName().compare(name) == 0)
            res.push_back(node);
    };

    traverse(searchFunc);

    return res;
}

void Tree::traverse(std::function<void(TreeNode*)> func)
{

    std::function<void(TreeNode*, std::function<void(TreeNode*)>&)> recurseF = [&](TreeNode* node, std::function<void(TreeNode*)>& func)
    {
        if(node == nullptr)
            return;

        recurseF(node->mLeft, func);
        recurseF(node->mRight, func);

        func(node);
    };

    recurseF(this->mAnchor, func);
}

void Tree::traverseConst(std::function<void(const TreeNode*)> func) const
{

    std::function<void(const TreeNode*, std::function<void(const TreeNode*)>&)> recurseF = [&](const TreeNode* node, std::function<void(const TreeNode*)>& func)
    {
        if(node == nullptr)
            return;

        recurseF(node->mLeft, func);
        recurseF(node->mRight, func);

        func(node);
    };

    recurseF(this->mAnchor, func);
}

void Tree::printTree(std::ostream& stream) const
{
    stream << "ID | Name       | Alter | Einkommen |  PLZ  | Pos" << std::endl;
    stream << "---+------------+-------+-----------+-------+-------" << std::endl;

    auto printFunc = [&](const TreeNode* node)
    {
        auto fillSpaceFunc = [&](size_t spacesAvailable, const std::string& str)
        {
            size_t spaces = spacesAvailable - str.length();
            for(size_t i = 0; i < spaces; ++i)
            {
                stream << " ";
            }
        };

        //print ID
        auto nodeId = std::to_string(node->getNodeId());
        stream << nodeId;

        fillSpaceFunc(3, nodeId);

        stream << "|";

        //print name
        fillSpaceFunc(12, node->getName());

        stream << node->getName();
        stream << "|";

        //print age
        auto age = std::to_string(node->getAge());

        fillSpaceFunc(7, age);

        stream << age;
        stream << "|";

        //print einkommen
        auto income = std::to_string(node->getIncome());

        fillSpaceFunc(11, income);

        stream << income;
        stream << "|";

        //print PLZ
        auto plz = std::to_string(node->getPLZ());

        fillSpaceFunc(7, plz);

        stream << plz;
        stream << "|";

        //print pos
        stream << node->getNodePosId();
        stream << std::endl;
    };

    traverseConst(printFunc);
}

void Tree::printNode(TreeNode* node, std::ostream& stream)
{
    stream << "NodeID: " << node->getNodeId() << ", Name: " << node->getName() << ", Alter: " << node->getAge() << ", Einkommen: "
           << node->getIncome() << ", PLZ: " << node->getPLZ() << ", PosID: " << node->getNodePosId() << std::endl;
}

TreeNode* Tree::insertNode(TreeNode* node, TreeNode* newNode)
{
    if(node == nullptr)
        return newNode;
    else
    {
        if(newNode->getNodePosId() <= node->getNodePosId())
            node->mLeft = insertNode(node->mLeft, newNode);
        else
            node->mRight = insertNode(node->mRight, newNode);
    }

    return node;
}
