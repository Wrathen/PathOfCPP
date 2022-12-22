// Big shout-out to https://chat.openai.com
// I have chatted with the AI, forcing it to make me a QuadTree, but in the process of making
// I have learnt so much. I have told it the stuff it's doing wrong and what I need etc...
// In the process, there has been many stuff considered.
// After an hour, I decided I don't even want a QuadTree in this game! LMAO! ICANT SMH!
// But just in case, I'll keep this stuff here. It's insane how easy it is nowadays. Wow...
// This has been an eye-opening session for me. Wow... Really...

#pragma once
#include <cstddef>
#include <vector>

template <typename T>
class QuadTreeNode {
public:
    QuadTreeNode(const T& value, size_t x, size_t y, size_t width, size_t height)
        : value_(value), x_(x), y_(y), width_(width), height_(height) {}

    T value_;
    size_t x_;
    size_t y_;
    size_t width_;
    size_t height_;
    QuadTreeNode* children_[4] = { nullptr };
};

template <typename T>
class QuadTree {
public:
    QuadTree(size_t width, size_t height) : root_(nullptr, 0, 0, width, height) {}

    void Insert(const T& value, size_t x, size_t y) {
        Insert(&root_, value, x, y);
    }

    std::vector<T> Query(size_t x, size_t y, size_t width, size_t height) const {
        std::vector<T> result;
        Query(&root_, x, y, width, height, &result);
        return result;
    }

private:
    QuadTreeNode<T> root_;

    void Insert(QuadTreeNode<T>* node, const T& value, size_t x, size_t y) {
        if (node->children_[0] == nullptr) {
            // Leaf node
            node->value_ = value;
            return;
        }

        // Find the quadrant in which the point (x, y) lies
        size_t quadrant = 0;
        if (x >= node->x_ + node->width_ / 2) {
            quadrant += 1;
        }
        if (y >= node->y_ + node->height_ / 2) {
            quadrant += 2;
        }

        // Recurse on the appropriate child
        Insert(node->children_[quadrant], value, x, y);
    }

    void Query(const QuadTreeNode<T>* node, size_t x, size_t y, size_t width, size_t height, std::vector<T>* result) const {
        // Check if the query region is completely outside the current node
        if (x + width <= node->x_ || x >= node->x_ + node->width_ ||
            y + height <= node->y_ || y >= node->y_ + node->height_) {
            return;
        }

        // Check if the current node is completely inside the query region
        if (x <= node->x_ && x + width >= node->x_ + node->width_ &&
            y <= node->y_ && y + height >= node->y_ + node->height_) {
            result->push_back(node->value_);
            return;
        }

        // Otherwise, the query region and the current node intersect
        if (node->children_[0] == nullptr) {
            result->push_back(node->value_);
            return;
        }

        // Recurse on the children
        for (size_t i = 0; i < 4; i++) {
            Query(node->children_[i], x, y, width, height, result);
        }
    }

    void Split(QuadTreeNode<T>* node) {
        size_t x = node->x_;
        size_t y = node->y_;
        size_t width = node->width_;
        size_t height = node->height_;

        node->children_[0] = new QuadTreeNode<T>(T(), x, y, width / 2, height / 2);
        node->children_[1] = new QuadTreeNode<T>(T(), x + width / 2, y, width / 2, height / 2);
        node->children_[2] = new QuadTreeNode<T>(T(), x, y + height / 2, width / 2, height / 2);
        node->children_[3] = new QuadTreeNode<T>(T(), x + width / 2, y + height / 2, width / 2, height / 2);
    }
};