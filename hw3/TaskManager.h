
#pragma once

#include <memory>

#include "Person.h"
#include "Task.h"
#include "SortedList.h"

//****************************************************************************//
/**
 * @brief Class managing tasks assigned to multiple persons.
 */
class TaskManager {
     /**
     * @brief Maximum number of persons the TaskManager can handle.
     */
     static const int MAX_PERSONS = 10;

     /**
     * @brief Array of unique pointers to Person objects
     */
     std::unique_ptr<Person> m_persons[MAX_PERSONS];

     /**
      * @brief Number of persons in the array
      */
     int m_size;

     /**
      * @brief Unique value identifier for evry new task
      */
     int m_tasksId;

     /**
      * @brief Functor to filter tasks by type.
      * @param type The type of tasks to be filtered.
      * @return True if the task is of the specified type, false otherwise.
      */
     struct TasksByType;

     /**
      * @brief Functor to bump task priority.
      * @param priority The amount by which the priority will be increased.
      * @return New task with the bumped priority.
      */
     struct BumpTaskPriority;

     /**
      * @brief Returns the index of the person with the specified name.
      * @param personName The name of the person to search for.
      * @return The index of the person with the specified name, or -1 if not found.
      */
     int getIdxForPerson(const string& personName) const;

public:

     /**
     * @brief Default constructor to create a TaskManager object.
     *
     * Note - you may add =default if needed.
     */
     TaskManager();

     /**
     * @brief Deleted copy constructor to prevent copying of TaskManager objects.
     */
     TaskManager(const TaskManager &other) = delete;

     /**
     * @brief Deleted copy assignment operator to prevent assignment of TaskManager objects.
     */
     TaskManager &operator=(const TaskManager &other) = delete;

     /**
     * @brief Assigns a task to a person.
     *
     * @param personName The name of the person to whom the task will be assigned.
     * @param task The task to be assigned.
     */
     void assignTask(const string &personName, const Task &task);

     /**
     * @brief Completes the highest priority task assigned to a person.
     *
     * @param personName The name of the person who will complete the task.
     */
     void completeTask(const string &personName);

     /**
     * @brief Bumps the priority of all tasks of a specific type.
     *
     * @param type The type of tasks whose priority will be bumped.
     * @param priority The amount by which the priority will be increased.
     */
     void bumpPriorityByType(TaskType type, int priority);

     /**
     * @brief Prints all employees and their tasks.
     */
     void printAllEmployees() const;

     /**
     * @brief Prints all tasks of a specific type.
     *
     * @param type The type of tasks to be printed.
     */
     void printTasksByType(TaskType type) const;

     /**
     * @brief Prints all tasks assigned to all employees.
     */
     void printAllTasks() const;
};


//****************************************************************************//

struct TaskManager::TasksByType {
     TaskType m_type;
     explicit TasksByType(const TaskType& type) : m_type(type) {}
     bool operator()(const Task& task) const {
          return task.getType() == m_type;
     }
};

//****************************************************************************//

struct TaskManager::BumpTaskPriority {
     int m_priority;
     explicit BumpTaskPriority(const int priority) : m_priority(priority) {}
     Task operator()(const Task& task) const {
          int newPriority = m_priority + task.getPriority();
          Task result(newPriority, task.getType(), task.getDescription());
          result.setId(task.getId());
          return result;
     }
};

//****************************************************************************//