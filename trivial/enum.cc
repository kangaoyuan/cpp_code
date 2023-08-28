// enumeration, which is not scoped, can directly use the cases.
//enum Color{
//    black,
//    white,
//    red,
//};

/* error, for redefinition. */
//bool white = false;

// enumerator, which is limited scope, must using enum_name::case with scope resolution. 
enum class _Color{
    black,
    white,
    red,
};

bool white = true;
