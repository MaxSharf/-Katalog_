#pragma once
#include <boost/filesystem/operations.hpp>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using namespace boost;

void CreateDir(string path, string namedir);
void RemoveDir(string path, string namedir);
void RenameDir(string path);
void PrintDir(string path);








