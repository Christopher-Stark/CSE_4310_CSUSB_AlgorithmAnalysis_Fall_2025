/* Implementation Booster Code Supplied by Prof. Voigt
* Missing Code (**COMPLETED** added comments explaining process) filled in by Student: Christopher Stark
* Date: November 11, 2025
* Course: CSE-4310-61
* Project: DFS Topological Sort with C++
* Description: Program Utilizes Depth-First Search to perform a topological sort
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
// prototypes
void DFS_TopoSort();
void DFS_Visit(string);
void print_graph();
void print_vinfo();
class Vertex
{
public:
	Vertex()
		: label("nolabel"), color("nocolor"), dtime(0), ftime(0)
	{
	}
	Vertex(string v)
		: label(v), color("WHITE"), dtime(0), ftime(0)
	{
	}
	string label;
	string color;
	int dtime;
	int ftime;
	void show() const
	{
		cout << label << " :: " << color << " :: " << dtime << " :: "
			<< ftime << endl;
		return;
	}
};
// global variables
map<string, vector<string> > GRAPH;
vector<string> COURSES;
map<string, Vertex> Vinfo;
int TIME;
vector<string> TopoSort;
int main()
{
	GRAPH["math_120"] = { "math_130", "cs_100" };
	GRAPH["math_130"] = { "math_140" };
	// ... complete for all courses ... **COMPLETED** Added remainder GRAPH mapping of courses with adjacent vertices
	GRAPH["cs_100"] = {"cs_200"};
	GRAPH["math_140"] = {"cs_150", "math_200"};
	GRAPH["cs_150"] = {"cs_200"};
	GRAPH["cs_200"] = {"cs_240"};
	GRAPH["eng_100"] = {"cs_200"};
	GRAPH["phys_130"] = {"math_200"};
	GRAPH["math_200"] = { };
	GRAPH["cs_240"] = { };
	// ...complete and uncomment **COMPLETED** Added all Courses to COURSES Global vector
	COURSES = { "math_120", "math_130", "cs_100", "math_140", "cs_150", "cs_200", "eng_100", "phys_130", "math_200", "cs_240" };
	DFS_TopoSort();
	return 0;
}
// FUNCTION DEFINITIONS
// prints each vertex in COURSES (by label) with list of adjacent
// vertices;
void print_graph()
{
	for (int i = 0; i < COURSES.size(); ++i)
	{
		cout << COURSES[i] << " --> ";
		for (int j = 0; j < GRAPH[COURSES[i]].size(); ++j)
			cout << GRAPH[COURSES[i]][j] << " ";
		cout << endl;
	}
	return;
}
// prints each vertex in COURSES with its properties
void print_vinfo()
{
	cout << endl;
	for (int i = 0; i < COURSES.size(); ++i)
		Vinfo[COURSES[i]].show();
	cout << endl;
	return;
}
// top-level DFS function with add-on to collect
// and report topological sort
void DFS_TopoSort()
{
	Vinfo.clear(); // reset global variables
	TIME = 0;
	TopoSort.clear();
	// initialize Vinfo
	for (int i = 0; i < COURSES.size(); ++i)
	{
		Vinfo[COURSES[i]] = Vertex(COURSES[i]);
	}
	// print graph ... complete ...**COMPLETED** Called correct Prof. supplied function
	print_graph();
	// print Vinfo as initialized ... complete ...**COMPLETED** Called correct Prof. supplied function
	print_vinfo();
	// outer loop; iterates over all vertices by label
	// here: course number
	for (int i = 0; i < COURSES.size(); ++i)
	{
		string u = COURSES[i];
		if (Vinfo[u].color == "WHITE")
		{
			// ... complete ...**COMPLETED** call DFS_Visit Function for current COURSE, which then recursively calls itself when needed
			DFS_Visit(u);
		}
		else
		{
			// ... complete ...**COMPLETED** If != WHITE we just continue with for loop
			continue;
		}
	}
	// all vertices have been processed
	// print final Vinfo ... complete ...**COMPLETED** Called correct Prof. supplied function returning finalized TopoSort Vector
	print_vinfo();
	cout << "\nDFS and Topological Sort Done" << endl << endl;
	cout << "VERTICES LISTED IN TOPOLOGICAL SORT:" << endl;
	// print out topological order by printing TopoSort
	// ... complete ...**COMPLETED** For loop to print finalized TopoSort Vector
	for (int i = 0; i < TopoSort.size(); ++i)
	{
		cout << TopoSort[i] << endl;
	}
	return;
}
// called by DFS_Toposort(); recursive DFS process from vertex u
void DFS_Visit(string u)
{
	// update time ... complete ...**COMPLETED** Incremented ++ to Global TIME Variable
	TIME++;
	// set discover time and color of vertex u ... complete ... 
	// **COMPLETED** Used map class structure to assign dtime,color with global Vinfo Vector of current COURSE string u
	Vinfo[u].dtime = TIME;
	Vinfo[u].color = "GRAY";
	cout << "DFS_Visit: vertex " << u
		<< " going from WHITE to GRAY at time "
		<< TIME << endl;
	// ... complete and uncomment ... **COMPLETED** Set adjacents vector to GRAPH of COURSE Variable (adjacents of current COURSE)
	vector<string> adjacents = GRAPH[u];
	for (int i = 0; i < adjacents.size(); ++i)
	{
		string v = adjacents[i];
		if (Vinfo[v].color == "WHITE")
		{
			DFS_Visit(v);
		}
		else
		{
			continue;
		}
		// ... complete ...**COMPLETED** Finished for loop to iterate over remainder adjacent vertices using DFS_Visit Function 
	}
	// update TIME ... complete ... **COMPLETED** Incremented ++ to Global TIME Variable
	TIME++;
	// set color and finish time of vertex u
	// ... complete ... 
	// **COMPLETED** Used map class structure to assign ftime,color with global Vinfo Vector of current COURSE string u
	Vinfo[u].ftime = TIME;
	Vinfo[u].color = "BLACK";
	cout << "DFS_Visit: vertex " << u
		<< " going from GRAY to BLACK at time = "
		<< TIME << endl;
	// add vertex u to TopoSort (this is L in the lecture video)
	// ... complete ... **COMPLETED** Inserted fully explored vertex of current COURSE string u to the front of TopoSort Vector 
	TopoSort.insert(TopoSort.begin(), u);
	return;
}