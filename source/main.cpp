#include "flight_code.h"
#include "file_reader.h"

int main() {
    file_reader_t fr({"test_input/file_1, test_input/file_2"}, {"test_output/file_1, test_output/file_2"});

    if (!fr.read_files())
        return 1;
    if (!fr.write_files())
        return 2;

    return 0;
}