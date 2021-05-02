#include <regex>
#include <cstdio>
#include <string>
#include "obj_loader.hpp"

const size_t max_filename_size = 256;

void le_regex_test()
{
    std::string number = "123.45";
    std::regex regex{R"(\d+.\d+)"};

    if(std::regex_match(number, regex))
        printf("regex matches string\n");
    else
        printf("regex doesn't match in string\n");
}

std::ifstream get_input_file(const std::string& filename)
{
    printf("Opening file %s...\n", filename.c_str());

    std::ifstream input_file{filename};
    if(!input_file.is_open()) 
    {
        printf("Couldn't open file. Exiting...\n");
        exit(1);
    }
    printf("File opened!\n");


    return input_file;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Please provide an input .obj file\n");
        exit(1);
    }

    const std::string filename{argv[1]};

    auto input_file = get_input_file(filename);

    auto tokens = load_obj(input_file);



    input_file.close();
    return 0;
}
