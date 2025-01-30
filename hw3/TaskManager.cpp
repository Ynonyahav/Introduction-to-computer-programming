#include "TaskManager.h"

//****************************************************************************//

TaskManager::TaskManager() : m_persons{nullptr}, m_size(0), m_tasksId(0) {}

//****************************************************************************//

int TaskManager::getIdxForPerson(const string& personName) const{
    for (int index = 0; index < MAX_PERSONS; index++) {
        if (m_persons[index] == nullptr ||
            m_persons[index]->getName() == personName) return index;
    }
    return -1;
}

//****************************************************************************//

void TaskManager::assignTask(const string &personName, const Task &task) {
    int index = getIdxForPerson(personName);
    if (index < 0 || m_size > MAX_PERSONS) {
        throw std::runtime_error("System is Full");
    }
    if (!m_persons[index]) {
        m_persons[index] = std::make_unique<Person>(personName);
        m_size++;
    }
    Task taskWithId(task.getPriority(), task.getType(), task.getDescription());
    taskWithId.setId(m_tasksId++);
    m_persons[index]->assignTask(taskWithId);
}

//****************************************************************************//

void TaskManager::completeTask(const string &personName) {
    int index = getIdxForPerson(personName);
    if (index >= 0 && m_persons[index]) {
        m_persons[index]->completeTask();
    }
}

//****************************************************************************//

void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    if (priority > 0) {
        const TasksByType filterFunctor(type);
        const BumpTaskPriority applyFunctor(priority);

        for (int i = 0; i < m_size; i++) {
            SortedList<Task> taskList = m_persons[i]->getTasks();
            SortedList<Task> filteredList = taskList.filter(filterFunctor);
            SortedList<Task> appliedList = filteredList.apply(applyFunctor);

            m_persons[i]->setTasks(appliedList);
            for (const Task& task : taskList) {
                if (task.getType() != type) {
                    m_persons[i]->assignTask(task);
                }
            }
        }
    }
}

//****************************************************************************//

void TaskManager::printAllEmployees() const {
    for (int i = 0; i < m_size; i++){
            std::cout << *m_persons[i] << std::endl;
    }
}

//****************************************************************************//

void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> tasksList;
    for (int i = 0; i < m_size; i++) {
        SortedList<Task> taskList = m_persons[i]->getTasks();
        for (const auto & it : taskList) {
            if (it.getType() == type) {
                tasksList.insert(it);
            }
        }
    }
    for (const auto & it : tasksList) {
        std::cout << it << std::endl;
    }
}

//****************************************************************************//

void TaskManager::printAllTasks() const {
    SortedList<Task> tasksList;
    for (int i = 0; i < m_size; i++) {
        SortedList<Task> taskList = m_persons[i]->getTasks();
        for (const auto & it : taskList) {
            tasksList.insert(it);
        }
    }
    for (const auto & it : tasksList) {
        std::cout << it << std::endl;
    }
}

















