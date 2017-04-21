#include "tree.h"

#include <functional>

Tree::Tree()
    : mAnchor(nullptr), mNextId(0)
{
}

Tree::~Tree()
{

}

void Tree::insertNode(const std::string& name, int age, double income, int plz)
{
    TreeNode* newNode = new TreeNode(mNextId, name, age, income, plz);

    mAnchor = insertNode(mAnchor, newNode);

    ++mNextId;
}

bool Tree::deleteNode(int nodePosId)
{
    if(mAnchor->getNodePosId() == nodePosId)
    {

    }
    return false;
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

        func(node);

        recurseF(node->mLeft, func);
        recurseF(node->mRight, func);
    };

    recurseF(this->mAnchor, func);
}

void Tree::printTree(std::ostream& stream)
{
    stream << "ID | Name       | Alter | Einkommen |  PLZ  | Pos" << std::endl;
    stream << "---+------------+-------+-----------+-------+-------" << std::endl;

    auto printFunc = [&](TreeNode* node)
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

    traverse(printFunc);
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
