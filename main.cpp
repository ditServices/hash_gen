#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <iostream>
#include <filesystem>
#include <xxhash.h>

namespace fs = std::filesystem;
using namespace std;

uint64_t calc_xxh(fs::path source);

int main(int argc, char * argv[]) {

    if(argc < 2) {
        std::cout << "USEAGE: xxhash_gen [source_file]" << endl;
        return 0;
    }
    uint64_t result = calc_xxh(argv[1]);
    if(result != 0){
    cout << "HASH: ";
    std::cout << setfill('0') << setw(16) << std::hex << result << std::endl;
    } else {
        std::cout << "Hash/File Error" << endl;
    }

    return 0;
}

uint64_t calc_xxh(fs::path source) {

    size_t const bufferSize = 512;
    void * const buffer = malloc(bufferSize);
    if(buffer == nullptr) {
        free(buffer);
        return 0;
    }

    XXH64_state_t* const state = XXH64_createState();
    XXH64_hash_t const seed = 0;
    if(XXH64_reset(state, seed)) {
        free(buffer);
        return 0;
    }

    FILE *src = fopen(source.string().c_str(), "rb");
    if(!src) {
        free(buffer);
        return 0;
    }

    ssize_t bytes;
    while((bytes = fread(buffer, 1, bufferSize, src)) != 0) {
        if(bytes == 0) {
            free(buffer);
            return 0;
        }
        if(XXH64_update(state, buffer, bytes) == XXH_ERROR) {
            free(buffer);
            return 0;
        }
    }

    uint64_t digest = XXH64_digest(state);
    fclose(src);
    free(buffer);
    return digest;
}
