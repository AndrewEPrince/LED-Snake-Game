class Array {
private:
    int data[64]; // TODO: Replace "64" with "TOTAL_LEDS"
    int size;

public:
    Array() : size(0) {}

    void push_back(int value);
    void pop_back();
    int get_size() const;
    int operator[](int index) const;
};