/**
 *      file    :  test.cpp 
 *      author  :  techiedheeraj
 *      created :  2021 Jul 10 14:32:32 
 *      lastMod :  Sat 10 Jul 14:32:32 2021 
 **/

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

//#define LOCAL 1
#include						<bits/stdc++.h>
#ifdef LOCAL
#include						 "/Users/r00tdk/.vim/headers/pprint.hpp"
#else
#define trace 					//
#endif

#define ar array
#define ll						long long
#define sz(x)         (int)(x).size()
#define pii						pair<int, int>
#define pli						pair<ll, int>
#define pil						pair<int, ll>
#define pll						pair<ll, ll>
#define vi						vector<int>
#define vll						vector<ll>
#define vb						vector<bool>
#define vd						vector<double>
#define vs						vector<string>
#define ff						first
#define ss						second
#define pb						push_back
#define eb						emplace_back
#define ppb						pop_back
#define pf						push_front
#define ppf						pop_front
#define vpii					vector<pii>
#define umap					unordered_map
#define all(x)			 	x.begin(),x.end()
#define clr(a,b)			memset(a,b,sizeof a)
#define fr(i, n)			for(int i=0; i<n;++i)
#define fr1(i, n)			for(int i=1; i<=n; ++i)
#define rfr(i, n)			for(int i=n-1; i>=0; --i)
#define precise(x)		cout<<fixed<<setprecision(x)
typedef double				f80;

using namespace std;

#ifdef PBDS
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#endif

template <typename Arg1>
void prn(Arg1&& arg1)
{ cout << arg1 << "\n";}

template <typename Arg1, typename... Args>
void prn(Arg1&& arg1, Args&&... args)
{ cout << arg1 << " "; prn(args...); }

template <typename Arg1>
void prs(Arg1&& arg1)
{ cout << arg1 << " ";}

template <typename Arg1, typename... Args>
void prs(Arg1&& arg1, Args&&... args)
{ cout << arg1 << " "; prs(args...); }

template <typename Arg1>
void read(Arg1&& arg1)
{ cin >> arg1; }

template <typename Arg1, typename... Args>
void read(Arg1&& arg1, Args&&... args)
{ cin >> arg1; read(args...); }

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
  return '"' + s + '"';
}

string to_string(const char* s) {
  return to_string((string) s);
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}

template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

const long long MAX = (long long) 360 * (long long) 1e9;
const long double pi = acos((long double) -1.0);
const long double q = pi / MAX;

inline void solve(int funNum);
int main(int argc, char* argv[]) {
#ifdef LOCAL
  freopen("in.txt" , "r" , stdin);
  //freopen("out.txt" , "w" , stdout);
#else	
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
#endif
  int t = 1;
//  read(t);
  fr1 (tc, t) {
    solve(stoi(argv[1]));
  }
  return 0;
}
/* 
 * This program is to analyse the concurrency in c++
 */

// common memory
int acc = 0; // variable will store all the sum of squares of numbers from 1 to 20

/* Using default implementation */
void threadFunc1(int x) {
  acc += x *x; // race condition as many thread are accessing the same global variable
}

inline void solve1() { // associated for threadFunc1
  vector<thread>ths;

  for (int i = 1; i <= 20; ++i)
    ths.push_back(thread(&threadFunc1, i));

  for (auto&th: ths)
    th.join();

  cout << acc << endl;
}

/* Using reference */
void threadFunc2(int x, int& ac) {
  ac += x *x; // still race condition may occur as memory is common even if passed by reference
}

inline void solve2() { // associated for threadFunc2
  vector<thread>ths;

  for (int i = 1; i <= 20; ++i)
    ths.push_back(thread(&threadFunc2, i, ref(acc)));

  for (auto&th: ths)
    th.join();

  cout << acc << endl;
}

/* Using Mutex */
std::mutex mutexVar;
void threadFunc3(int x) {
  int temp = x *x; // always make calculations outside the mutext to acquire mutex for less time as possible
  mutexVar.lock();
  acc += temp; // there will not be any race conditions as other threads will be on halt till acc is updated with valid value
  mutexVar.unlock();
}

inline void solve3() { // associated for threadFunc2
  vector<thread>ths;

  for (int i = 1; i <= 20; ++i)
    ths.push_back(thread(&threadFunc3, i));

  for (auto&th: ths)
    th.join();

  cout << acc << endl;
}

/* Using Atomic (introduced in c++11 )*/
atomic<int> val(0);

void threadFunc4(int x) {
  val += x*x; // x*x is evaluated before handed over to val, so it will be outside the atomic event
}

inline void solve4() { // associated for threadFunc2
  vector<thread>ths;

  for (int i = 1; i <= 20; ++i)
    ths.push_back(thread(&threadFunc4, i));

  for (auto&th: ths)
    th.join();

  cout << "val " << val << endl;
}

/* Using Tasks:
 * An even higher level of abstraction avoids the concept of threads altogether and talks in terms of tasks instead
 *
 * The async construct uses an object pair called a promise and a future. The former has made a promise to eventually provide a value. The future is linked to the promise and can at any time try to retrieve the value by get(). If the promise hasn't been fulfilled yet, it will simply wait until the value is ready. The async hides most of this for us, except that it returns in this case a future<int> object. Again, since the compiler knows what this call to async returns, we can use auto to declare the future.
 */

int square1(int x) {
  return x*x;
}
  
inline void solve5() {
  vector<future<int>>fs;

  for (int i = 1; i <=20; ++i) {
    fs.push_back(async(&square1, i));
  }

  for (future<int>&v: fs)
    acc+=v.get();

  cout << "promised value " << acc << endl;
}

/* Using Tasks:
 * explicitly giving async 
 * All the threads are running in parallel
 */

int square2(int x) {
  cout << " <<< x is >>> " << x << endl;
  this_thread::sleep_for(chrono::milliseconds(100));
  return x*x;
}
  
inline void solve6() {
  vector<future<int>>fs;

  for (int i = 1; i <=20; ++i) {
    fs.push_back(async(launch::async, &square2, i));
  }

  cout << "thread id : "<< this_thread::get_id() << endl;
  for (future<int>&v: fs)
    acc+=v.get();

  cout << "promised value " << acc << endl;
}

/* Condition Variable
 *
 *
 * If we return to threads, it would be useful to be able to have one thread wait for another thread to finish processing something, essentially sending a signal between the threads. This can be done with mutexes, but it would be awkward. It can also be done using a global boolean variable called notified that is set to true when we want to send the signal. The other thread would then run a for loop that checks if notified is true and stops looping when that happens. Since setting notified to true is atomic and in this example we're only setting it once, we don't even need a mutex. However, on the receiving thread we are running a for loop at full speed, wasting a lot of CPU time. We could add a short sleep_for inside the for loop, making the CPU idle most of the time.
 * A more principled way however is to add a call to wait for a condition variable inside the for loop.
 *
 *First of all, we're using some new syntax from C++11, that enables us to define the thread functions in-place as anynomous functions. They are implicitly passed the local scope, so they can read and write value and notified. If you compile it as it is, it will output 100 most of the time. However, we want the reporter thread to wait for the assigner thread to give it the value 20, before outputting it. You can do this by uncommenting the two blocks in either thread function. In the assigner thread, it will set notified to true and send a signal through the condition variable cond_var. In the reporter thread, we're looping as long as notified is false, and in each iteration we wait for a signal. Try running it, it should work.

But wait, if cond_var can send a signal that will make the call cond_var.wait(lock) blocking until it receives it, why are we still using notified and a for loop? Well, that's because the condition variable can be spuriously awaken even if we didn't call notify_one, and in those cases we need to fall back to checking notified. This for loop will iterate that many times.

This is a simplified description since we are also giving wait the object lock, which is associated with a mutex m. What happens is that when wait is called, it not only waits for a notification, but also for the mutex m to be unlocked. When this happens, it will acquire the lock itself. If cond_var has acquired a lock and wait is called again, it will be unlocked as long as it's waiting to acquire it again. This gives us some structure of mutual exclusion between the two threads,
 *
 */

condition_variable cond_var;
mutex m;

void solve7() {

  int value = 100;
  bool notified = false;

  thread reporter([&]() {
    unique_lock<mutex> lock(m);

    while(!notified) {
      cond_var.wait(lock);
    }
    cout << "value is " <<  value << "\n";
  });

  thread assigner([&]() {
      value = 20;
      notified = true;
      cond_var.notify_one();
  });

  reporter.join();
  assigner.join();
}

void producer_consumer() {
  mutex m1;
  condition_variable condVar;
  queue<int>q;
  bool done = false;
  int c = 0;

  thread producer([&]() {

    for (int i= 1;i <= 500; ++i) {
      std::unique_lock<mutex> lock(m1); // acquire the mutex lock and release it once goes out of scope
      cout << "pushed value is " << i << "\n";
      q.push(i);
      c++;
      condVar.wait(lock); // wait for consumer to finish reading
      //lock.unlock();
    }
    done = true;
  });

  thread consumer([&]() {

    while(!done) {
      std::unique_lock<mutex> lock(m1); // acquire the mutex lock
      cout << "size is " << q.size() << "\n";
      while(!q.empty()) {
        int v = q.front();
        q.pop();
        c--;
        cout << "popped value is  " << v << "\n";
      //  lock.unlock(); // unlock the mutex
        condVar.notify_one(); // notify the other thread
      }
    }
  });

  producer.join();
  consumer.join();

  cout << " c is " << c << "\n";
}

void solve(int funNum) {

  switch(funNum) {
    case 1:
      solve1();
      break;
    case 2:
      solve2();
      break;
    case 3:
      solve3();
      break;
    case 4:
      solve4();
      break;
    case 5:
      solve5();
      break;
    case 6:
      solve6();
      break;
    case 7:
      solve7();
      break;
    case 8:
      producer_consumer();
      break;
    default:
      cout << "enter valid value" << endl;
      break;
  }
}
