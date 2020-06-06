#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "rubiks_cube.h"
#include <thread>
#include <mutex>
#include <vector>
#include <future>
#include <queue>
#include <condition_variable>
#include <functional>
#include <stdlib.h>
#include <cstring>
#include <memory>
/*
 * Leaving the commented code in to show the thought process to getting to the best solution I could come up with to build the breadfirst-search tree structure.
 *
 *
 */

// Move this to main so ThreadPool becomes generic.
//using Path = std::vector<std::pair<Move, Rubiks_cube>>;

// New Path structure to save memory (by only saving the last Rubiks_cube)
/*
class Path
{
public:
    Path() { length = 0; moves = new Move[21]; }
    ~Path() { delete[] moves; }
    auto begin() { return moves; }
    auto end() { return moves + length; }
    Path(const Path& p): length(p.length), cube(p.cube), moves(new Move[21]) { for (unsigned i = 0; i < length; i++) moves[i] = p.moves[i]; }
    Path& operator=(const Path& p) { for (unsigned i = 0; i < p.length; i++) { moves[i] = p.moves[i]; } cube = p.cube; length = p.length; return *this; }
    void push_back(std::pair<Move, Rubiks_cube> pair) { moves[len last Rubiks_cube)
/*gth++] = pair.first; cube = pair.second; }
    std::pair<Move, Rubiks_cube> back() { return std::make_pair(moves[length-1], cube); }
    int size() { return length; }
private:
    unsigned length;
    Move* moves;
    Rubiks_cube cube;
};
*/

// Node, Added in third iteration of Path to further decrease memory costs
struct Node;
struct Node {
    Node() { }
    Node(Move m, std::shared_ptr<Node> n): move(m), previous(n) { }
    Move move;
    std::shared_ptr<Node> previous;
};

class Path
{
public:
    Path():length(0) { }
    Path(const Path& p): length(p.length), cube(p.cube), move(p.move) { }
    auto begin() { return move; }
    int size() { return length; }
    std::shared_ptr<Node> getMove() { return move; }
    void pop() { move = move.get()->previous; length--; }
    void push_back(std::pair<Move, Rubiks_cube> pair) { move = std::make_shared<Node>(pair.first, move); cube = pair.second; length++; }

    std::pair<Move, Rubiks_cube> back() { return std::make_pair(move.get()->move, cube); }
    Path& operator=(const Path& p) { move = p.move; cube = p.cube; length = p.length; return *this; }
private:
    unsigned length;
    std::shared_ptr<Node> move;
    Rubiks_cube cube;
};

typedef void (*Function)(Path);
struct Task
{
    Task(Function f, Path p);
    Task(Path p): path(p) { }
    Path path;
    static Function function;
};

class ThreadPool
{
private:
    std::queue<Task> tasks;
    std::mutex queue_mutex;
    std::condition_variable c_v;
    bool stop_running, quit;
    std::vector<std::thread> workers;
    void doWork();
public:
    ThreadPool(size_t threads = std::thread::hardware_concurrency());
    virtual ~ThreadPool() { abort(); }
    void abort();
    void clearTasks() { while(!tasks.empty()) { tasks.pop(); } }
    //template<class F, class... Args>
    //auto addWork (F&&, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
    void addWork(Task task);
    void stopRunning(bool stop = true) { stop_running = stop; }
    void createWorkers(int threads);

    void debug() { std::cout << tasks.size() << "\n"; }
};

#endif // THREADPOOL_H
