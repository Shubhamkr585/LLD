#include "UndoManager.hpp"

void UndoManager::addAction(const UndoAction& action) {
    std::lock_guard<std::mutex> lock(mtx);
    undoStack.push(action);
    while (!redoStack.empty()) redoStack.pop();
}
void UndoManager::undo() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!undoStack.empty()) {
        auto action = undoStack.top();
        undoStack.pop();
        action();
        redoStack.push(action);
    }
}
void UndoManager::redo() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!redoStack.empty()) {
        auto action = redoStack.top();
        redoStack.pop();
        action();
        undoStack.push(action);
    }
}
bool UndoManager::canUndo() const { return !undoStack.empty(); }
bool UndoManager::canRedo() const { return !redoStack.empty(); }
