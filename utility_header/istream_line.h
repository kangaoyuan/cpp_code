#include <cassert>
#include <istream>
#include <iterator>

class istream_line{
public:
    class iterator{
    public:
        using value_type = std::string;
        using pointer = const value_type*;
        using reference = const value_type&;
        using difference_type = ptrdiff_t;
        using iterator_category_tag = std::input_iterator_tag; 

        iterator() = default;
        explicit iterator(std::istream& is): m_is(&is) {
            ++*this; 
        };

        reference operator*() const noexcept {
            assert(m_is != nullptr); 
            return m_line;
        }

        pointer operator->() const noexcept {
            assert(m_is != nullptr); 
            return &m_line;
        }
    
        iterator& operator++() const noexcept {
            assert(m_is != nullptr); 
            std::getline(*m_is, m_line);
        }




    private:
        std::string m_line;
        std::istream* m_is = {nullptr};
    };

};
