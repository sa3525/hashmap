#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <optional>

using namespace std;

template<class K, class V>
class OpenAddressing {
public:
    OpenAddressing(size_t size
    ) : size_(size), cont_(size_), count_(0) {
    }


    auto get_hash_code(const K &key)
    {
        if(key == 2) {
            //cout << "key is 2\n";
            return (unsigned long) 3;
        }

        return hash<K>{}(key) % size_;;
    }

    bool put(const K &key, const V &value) {
        size_t hash_value = get_hash_code(key);
        cout << "hash value for " << key << " is value " << hash_value << "\n";
        int i = hash_value;
        for (int j = 0; j < size_; i = (i + 1) % size_, ++j) {
            if (!cont_[i].has_value()) {
                break;
            }

            if (cont_[i].value().first == key) {
                cont_[i].value().second = value;
                return true;
            }
        }

        if(count_ >= size_)
            return false;

        cont_[i] = make_pair(key, value);
        count_++;
        return true;
    }

    const V& get(const K& key)
    {
        size_t hash_value = get_hash_code(key);

        for (int j = 0, i = hash_value; j < size_; i = (i + 1) % size_, ++j) {

            if (cont_[i].value().first == key) {
                return cont_[i].value().second;
            }
        }

        throw out_of_range("Key not in Hash map");
    }
private:
    size_t size_;
    vector<optional<pair<K, V>>> cont_;
    size_t count_;
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    OpenAddressing <int, int>hash_map(10);

    for(int i = 0; i < 10; ++i) {
        hash_map.put(i, 10*i);
    }
    for(int i = 0; i < 10; ++i) {
        cout  << " " << hash_map.get(i);
    }
    cout << "\n";

    hash_map.put(11, 110);
    hash_map.put(1, 1115);

    for(int i = 0; i < 10; ++i) {
        cout  << " " << hash_map.get(i);
    }
    //hash_map.get(11);

    return 0;
}
