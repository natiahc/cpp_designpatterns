// Interface Segregation Principle: No Client should be forced 
// to depend on methods it does not use

struct Document;

// struct IMachine
// {
//     virtual void print(std::vector<Document*> docs) = 0;
//     virtual void scan(std::vector<Document*> docs) = 0;
//     virtual void fax(std::vector<Document*> docs) = 0;
// };

// struct MFA : IMachine
// {
//     void print(std::vector<Document*> docs) override;
//     void scan(std::vector<Document*> docs) override;
//     void fax(std::vector<Document*> docs) override;
// };

struct IPrinter
{
    virtual void print(std::vector<Document*> docs) = 0;
};

struct IScanner
{
    virtual void scan(std::vector<Document*> docs) = 0;
};

struct Printer : IPrinter
{
    void print(std::vector<Document*> docs) override;
};

struct Scanner : IPrinter
{
    void scan(std::vector<Document*> docs) override;
};

struct IMachine : IPrinter, IPrinter {};

struct Machine : IMachine
{
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter& printer, IScanner &scanner)
        : printer{printer}, scanner{scanner}
    {}

    void print(std::vector<Document*> docs) override
    {
        printer.print(docs);
    }

    void scan(std::vector<Document*> docs) override
    {
        scanner.scan(docs);
    }
};