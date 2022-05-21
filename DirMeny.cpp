#include "ShowMeny.h"
#include"DirMeny.h"

#include <boost/filesystem/operations.hpp>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using namespace boost;

uint32_t SizeDir(filesystem::path dir)
{
    size_t size = 0;
    for (filesystem::recursive_directory_iterator it(dir);
        it != filesystem::recursive_directory_iterator();
        ++it)
    {
        if (!filesystem::is_directory(*it))
            size += filesystem::file_size(*it);
    }
    return size;
}
struct HumanReadable {
    std::uintmax_t size{};
private:
    friend std::ostream& operator<<(std::ostream& os, HumanReadable hr) {
        int i{};
        double mantissa = hr.size;
        for (; mantissa >= 1024.; mantissa /= 1024., ++i) {}
        mantissa = std::ceil(mantissa * 10.) / 10.;
        os << mantissa << " " << "BKMGTPE"[i];
        return i == 0 ? os : os << "B ";
    }
    friend std::ostream& operator<<(std::ostream& os, uint32_t size) {
        int i{};
        double mantissa = size;
        for (; mantissa >= 1024.; mantissa /= 1024., ++i) {}
        mantissa = std::ceil(mantissa * 10.) / 10.;
        os << mantissa << " " << "BKMGTPE"[i];
        return i == 0 ? os : os << "B ";
    }
};
void CreateDir(string path, string namedir)
{
    boost::system::error_code error;
    boost::filesystem::create_directories(path + '/' + namedir, error);
    assert(!error);
}
void RemoveDir(string path, string namedir)
{
    try
    {
        if (boost::filesystem::exists(path + '/' + namedir))
        {
            boost::filesystem::remove_all(path + '/' + namedir);
        }
    }
    catch (boost::filesystem::filesystem_error const& e)
    {
        cout << e.what() << endl;
        std::system("pause");
    }
}
void RenameDir(string path)
{
    string old_name, new_name;
    cout << "Enter old name dir: ";
    getline(cin, old_name);
    cout << "Enter new name dir: ";
    getline(cin, new_name);
    try
    {
        if (boost::filesystem::exists(path + '/' + old_name))
        {
            boost::filesystem::rename(path + '/' + old_name, path + '/' + new_name);
        }
    }
    catch (boost::filesystem::filesystem_error const& e)
    {
        cout << e.what() << endl;
        std::system("pause");
    }
}
void PrintDir(string path)
{
    filesystem::directory_iterator begin(path);
    filesystem::directory_iterator end;
    filesystem::path file;
    cout << "\t" << left << setfill(' ') << setw(45) << "Filename" << "Size" << right << setfill(' ') << setw(50) << "Type" << endl;
    for (; begin != end; ++begin)
    {
        filesystem::file_status fs = boost::filesystem::status(*begin);
        file = *begin;
        cout << left << setfill(' ') << setw(45) << file.filename().string();
        switch (fs.type()) {
        case filesystem::regular_file:
            std::cout << HumanReadable{ boost::filesystem::file_size(*begin) } << right << setfill(' ') << setw(50) << "FILE" << endl;
            break;
        case filesystem::symlink_file:
            std::cout << HumanReadable{ SizeDir(*begin) } << right << setfill(' ') << setw(50) << "SYMLINK" << endl;
            break;
        case filesystem::directory_file:
            std::cout << HumanReadable{ SizeDir(*begin) } << right << setfill(' ') << setw(50) << "DIRECTORY" << endl;
            break;
        default:
            std::cout << HumanReadable{ SizeDir(*begin) } << right << setfill(' ') << setw(50) << "OTHER" << endl;
            break;
        }
    }
}