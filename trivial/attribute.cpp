#include  <iostream>

enum class [[nodiscard]] ErrorCode {
    OK,
    IO_ERROR
};

ErrorCode read_init(int& value){
    return value % 2 == 1 ? ErrorCode::OK : ErrorCode::IO_ERROR;
}

int test(int a, int b, [[maybe_unused]] int c){
    int result = a + b;
#ifdef ENABLE_FEATURE_C
    result += c;
#endif
    return result;
}


int main(){
    int x = 0;
    int y = 0;
    int result = 0;

    std::cin >> x >> y;
    switch(x){
        case 2:
            if (y % 2 == 0) {
                result++; 
                [[fallthrough]];
            } else {
                break; 
            }
        default:
            result++;
    }

    std::cout << result << std::endl;

    // trigger warning
    // read_init(result);
    // avoid [[nodiscard]] warning
    (void) read_init(result);

    std::cout << test(1, 2, 3) << std::endl;

    return 0;
}
