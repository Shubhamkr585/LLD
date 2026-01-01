#pragma once
// Design Pattern: Command (stores undo/redo actions as command objects)
#include <functional>
#include <stack>
#include <mutex>

class UndoManager {
public:
    using UndoAction = std::function<void()>;
    void addAction(const UndoAction& action);
    void undo();
    void redo();
    bool canUndo() const;
    bool canRedo() const;
private:
    std::stack<UndoAction> undoStack;
    std::stack<UndoAction> redoStack;
    std::mutex mtx;
};
