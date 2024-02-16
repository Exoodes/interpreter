class NullStream : public std::ostream {
    class NullBuffer : public std::streambuf {
    public:
        int overflow( int c ) { return c; }
    } buffer;

public:
    NullStream()
        : std::ostream( &buffer )
    {}
};