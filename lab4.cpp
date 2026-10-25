#define _CRT_SECURE_NO_WARNINGS // Visual Studio: suppress warnings for strcpy etc. (not needed by every compiler)
#include <iostream>
#include <cstring>

// scoping in C++
// in C++, a portion of code delimited by { } is called a block
// variables (and only them), REGARDLESS of their type, are only "alive" (accesible and usable) while we are still inside the block where they were defined -> that's called the scope of a variable
// when a local variable's block ends, that variable stops existing
// HOWEVER, if that variable is a pointer to dynamically allocated memory,
// only the pointer disappears, NOT the memory allocated with new!
// if we lose our last pointer to that memory without deleting it,
// we have a MEMORY LEAK !!!
// for e.g.:
/*
int x = 5;
if (x == 5) {
    int y = 6;
}
else {
    int z = 7;
}
*/

// in that example, y and z are defined within a small block inside that if-else, and they are only usable only inside the blocks where they were defined
// trying to use them outside of that will yield and error
// if you need to solve such cases, declare y and z before that, in a bigger block whose scope would suffice for your needs and only initialize them in that if-else
// variables defined inside a block are called LOCAL variables
// aside from those, we also have GLOBAL variables, variables which are defined outside of any blocks and can be used from anywhere in our program
// they are deleted once the program ends

char glob[] = "Hello from the global realm!"; // this is an example of a global variable

// how we pass parameters
// we have 3 ways of passing parameters to a function: pass-by-value, pass-by-reference and pass-by-pointer

void byValue(int x) { // pass-by-value
    // in pass-by-value, each argument that we send is actually a copy of the variable
    // before passing the parameters to a function, the compilar makes a copy of them and sends that instead
    // such that any changes to that parameter inside the function DOESN'T reflect outside of it
    x = 100; // x here is a COPY, so this only changes the local copy, not the actual variable that we sent
    std::cout << "Inside byValue: " << x << std::endl;
}

void byReference(int& x) { // pass-by-reference
    // in pass-by-reference, the parameter becomes another name
    // for the ORIGINAL variable, instead of being a separate copy
    // so modifying it will also modify the original variable
    // int& means x is a REFERENCE to an int, not a separate int
    // beware: & in a declaration means reference,
    // while &a in an expression means "address of a"
    x = 200; // x is another name for the ORIGINAL variable, so this will also change our parameter
}

void byPointer(int* x) { // pass-by-pointer
    // in pass-by-pointer, the compiler again sends a copy of the variable, but its a bit more tricky
    // the parameter being sent here is a copy, so not our original pointer, so modifying the address that it holds WON'T reflect outside the function
    // however, since this is a pointer type and it still points to the same address as our original pointer, modifying the value at the address it points WILL reflect outisde of the function and modify the data we held there
    if (x != nullptr) // pointers can be nullptr, so we should ALWAYS check before dereferencing
        *x = 300; // this will actually change the value we hold in our pointer, and WILL reflect outside
}

void changePointerLocally(int* p) {
    p = nullptr; // only our local COPY of the pointer becomes nullptr, not the one outside
    std::cout << "Inside changePointerLocally, p == nullptr: " << (p == nullptr) << std::endl;
}

// how we return things
// we also have 3 ways of returning things from a function, identical to how we pass them: return-by-value, return-by-reference and return-by-pointer

int returnByValue(int x) { // return-by-value
    int y = x + 1;
    return y; // similar to pass-by-value, in this case we receive a COPY of the value that's actually being returned
    // y is a local variable and stops existing when this function ends
    // but that's fine, since we return its VALUE, not its address!
    // the caller receives an independent int
}

int& returnByReference(int& x) { // return-by-reference
    return x;
    // we return a reference to the ORIGINAL variable that was passed to us
    // NOT a new local variable!
    // this is safe because the original variable still exists
    // after our function finishes
}

int* returnByPointer(int* x) { // return-by-pointer
    return x; // similar to pass-by-pointer, we also return a copy of the pointer (a copy of the pointer, NOT a copy of the actual data it holds!!!)
}

// !! NEVER do this:
// int& wrongReference() {
//     int x = 5;
//     return x; // WRONG: x disappears when the function ends!
//     // meaning "x" does not exist anymore when the function ends, and we return it meaning we will return a garbage value instead of what we wanted
// }
// int* wrongPointer() {
//     int x = 5;
//     return &x; // WRONG: same issue, but with a pointer!
// }

// classes
// in C++, classes offer us ways of creating complex structures by combining multiple (and different) data-types under the same name
// this same construct allows us to provide functionality to our structure, allowing us to utilize the variables we wrapped over in any ways we deem necessary
// classes allow us to basically model reality in our code and work organizedly, and they stand at the core of Object-Oriented-Programming
// instances of a class are called objects, and classes behave like any other data-type we have inside, just that it is defined by us and we give it further functionality than any other single basic data-type could ever have
// suppose you are making an online multiplayer game
// without classes, you'd have to find ways of keeping track of player stats for each player (meaning tens of arrays indexed by player ID), you'd have to constantly re-size those when new players joined and so on
// but with classes, you can have you player class, which encapsulates everything inside a single object, allowing you simple access for everything for a single player, leaving you only to manage the array of players itself


class Student { // SYNTAX: class <NameOfClass>
    // inside classes, we have what are called access modifiers
    // there are 3 access modifiers: public, private and protected
    // everything defined as public can be accessed from outside the class
    // everything private cannot be accessed from outside the class, and is only usable inside the definition of the class
    // and protected is related to inheritance, which we'll learn more about later, but for now we'll leave it aside
    private:
        // ideally, we'd want all our variables from inside a class or at least most of them to be private, such that we don't expose the inner workings of an object to the outside (this is called encapsulation)
        // we can then control what we expose by creating functions that allow outsiders to get the value of a field (getters) or to change it according to our own rules (setters)
        int age;
        char* name; // dynamically allocated field: WE own this memory
        // as with regular dynamic fields, we still have ownership over the memory we want to allocate inside of our class

    public:
        // before diving into the special functions inside of a class, I'd want to discuss with you something you'll see below, namely usage of "this->"
        // first of all, the arrow accessor is a way of accessing properties from a pointer-type (so, if we have an object created dynamically, we could get its age for e.g. by doing obj->age)
        // when we deal with non-dynamic objects, we use "." to access its properties (obj.age)
        // next, since we use "->", we can conclude that "this" is a pointer
        // the "this" pointer is an abstract modelling of classes, and basically refers to the current object as hand, its a pointer to the current object being manipulated
        // for e.g., if we have:
        // Student a; -> this will call the default constructor (see below), since we have initialized it without any arguments
        // inside that default constructor, the "this" pointer will be an actual pointer to the address of the "a" variable
        // if we then do "Student b;" below, when the program reaches the default constructor for "b", the "this" pointer will point to it (they'll differ)
        // then again, if we do below that "a.setAge(30);", when the setAge called from our class is called, the "this" pointer will point to "a"
        // its a tad abstract, but it is used as a reference to the current object being worked on, whatever that might be in the program, and whether the object itself is dynamic or not (this exists for absolutely all objects!!)
        // please get used to using it everywhere, since it is a good practice to use it to be able (both you and the compiler) to differentiate between what's coming from our class and what's coming from outside
        
        // since this is a custom object we created, we have to manage its lifetime ourselves, from creation to deletion
    
        // for creation, we have multiple special functions called constructors
        // they define how we create the object in different scenarios
        // for any intended purposes, in our class they must be public and only have the name of the class (no return type, they don't return anything)
    
        // DEFAULT constructor: called when we make a Student without arguments, allowing us to shape how the default object would look and what values
        // would our parameters take in that case
        Student() {
            this->age = 0;
            this->name = new char[1]; // even an empty C-string needs room for '\0'
            this->name[0] = '\0';
            std::cout << "Default constructor called" << std::endl;
        }

        // PARAMETERIZED constructor: allows us to define how we initialize the object with the values we receive from the outside
        // you can have as many of these as you want, for as many combinations of parameters as you'd like
        // the compiler will know what to call based on the number of parameters you give it and their type (called the function signature) -> for this, it'd be Student(const char*, int)
        // you can have multiple of those as long as their signatures DIFFER, since if you have Student(const char* name, int birthYear), even though that differs for us as they are different arguments, the compiler will see that that signature already exists (this function) and throw an error
        Student(const char* name, int age) {
            this->age = age;
            // if we didn't use "this", we'd write age = age;
            // this would COMPILE, but it would just assign the parameter to itself!
            // the parameter "age" shadows the field "age"
            // using this->age explicitly tells the compiler we mean the object's field
            // this is called shadowing (2 variables having the same name but in different contexts)
            if (name == nullptr)
                name = "";
            this->name = new char[std::strlen(name) + 1]; // +1 for '\0' !!
            std::strcpy(this->name, name);
            std::cout << "Parameterized constructor called" << std::endl;
        }

        // DESTRUCTOR: this is how we define the deletion process for our object
        // the destructor is called when the object reaches the end of its lifespan, or when we call delete on it (only if it is DYNAMIC!! - we cannot call delete on static memory)
        // for any intended purposes for us now, it is required only when we have dynamic fields inside of our class, and it allows us to clean the memory up properly, since the compiler doesn't know what to do with dynamic memory
        ~Student() {
            std::cout << "Destructor called for " << this->name << std::endl;
            delete[] this->name; // free what THIS object allocated
            this->name = nullptr;
        }

        int getAge() { // getter for the age field
            // since it is return-by-value, an actual value is returned and any changes to it won't affect our object's properties
            return this->age;
        }

        void setAge(int age) { // setter for the age field
            if (age >= 0) // encapsulation lets us reject invalid values
                this->age = age;
        }

        
        char* getName() { // WRONG: don't do this - this is just for showcasing purposes
            return this->name; // this is called shallow-copy, and is wrong
            // this returns a COPY OF THE POINTER, not a copy of the string!
            // both pointers will therefore point to the SAME memory
            // in this case, we return the actual pointer we hold for the name (a variable holding a copy of the pointer, but they both point to the same address), meaning the one the our Student object has the ownership of
            // if, after receiving this, the caller were to modify that value at the given address from the pointer, that change WOULD reflect back into our own object's properties, and we definitely do not want that
            // if it were to be deleted afterwards, that change would reflect back to us as well and our name would point to deallocated memory, which is undefined behaviour and will cause a lot of issues!
            // so never do shallow copies, whether it is for getters or setters
        }
        

        // SETTER: make a DEEP COPY instead of just doing name = newName; (that is another way of doing a shallow-copy - pointer assignment)
        // it will make both pointers point at the same address, and when any of them changes something at that address, that gets reflected into the other one as well
        // 
        // by using deep copies, the caller can modify/delete their original array safely afterward without that affecting us in any way
        void setName(const char* name) {
            if (name == nullptr)
                return;
            char* copy = new char[std::strlen(name) + 1];
            std::strcpy(copy, name);
            delete[] this->name;
            this->name = copy;
        }
        // this also showcases the principles behind resizing a dynamic array
        // we create a new one with the changed length and then copy our initial one into it
        // then make our original array point to that newly allocated memory with the changed length

        // DEEP COPY getter
        // we allocate NEW memory and copy the actual characters into it
        // this is a DEEP COPY of the string
        // the caller now owns the NEW array and must delete[] it later
        // any changes on the array he receives won't affect us and that's the way we want stuff to be
        char* getNameCopy() {
            char* copy = new char[std::strlen(this->name) + 1];
            std::strcpy(copy, this->name);
            return copy; // safe: the ARRAY lives on after the function returns
        }

        void print() {
            std::cout << "Student: " << this->name << ", age " << this->age << std::endl;
        }
};

int main() {
    // passing args
    int a = 10;
    byValue(a);
    std::cout << "After byValue: " << a << std::endl; // 10
    byReference(a);
    std::cout << "After byReference: " << a << std::endl; // 200
    byPointer(&a); // &a = address of a
    std::cout << "After byPointer: " << a << std::endl; // 300

    int* p = &a;
    changePointerLocally(p);
    std::cout << "p is still valid: " << *p << std::endl << std::endl;

    // returning things
    int b = returnByValue(a);
    std::cout << "Returned by value: " << b << std::endl; // 301
    returnByReference(a) = 400; // returned reference acts as another name for a
    std::cout << "a after reference return: " << a << std::endl; // 400
    int* returnedAddress = returnByPointer(&a);
    *returnedAddress = 500;
    std::cout << "a after pointer return: " << a << std::endl; // 500
    // IMPORTANT: reference/pointer returns are safe ONLY if the referenced object still exists.

    // blocks and lifespans
    int number = 7;
    {
        int inside = 99; // only exists inside this block { ... }
        std::cout << "Inside block: " << inside << std::endl;
        int number = 8; // SHADOWING: this is a DIFFERENT variable named number
        std::cout << "Inner number: " << number << std::endl;
    } // inside and the inner number stop existing here
    // std::cout << inside; // ERROR: inside is out of scope!
    std::cout << "Outer number: " << number << std::endl; // still 7

    int* heapNumber = new int(123);
    {
        int* temporaryPointer = heapNumber;
        std::cout << "Dynamic value: " << *temporaryPointer << std::endl << std::endl;
    } // temporaryPointer dies, but the allocated int DOES NOT disappear!
    delete heapNumber; // we must free the dynamically allocated int ourselves
    heapNumber = nullptr;
    // a local variable's scope/lifetime and a dynamic allocation's lifetime are DIFFERENT. !!!

    // classes

    Student first; // default constructor
    first.setName("Ana"); // since first is non-dynamic, we access stuff with "."
    first.setAge(19);
    first.print();
    // first.age = -10; // ERROR: age is private

    Student second("Mihai", 20); // parameterized constructor
    second.print();
    // !! IMPORTANT:
    // for now, DO NOT copy entire Student objects!
    // e.g. Student second = first;
    // we'll learn why this is dangerous for classes with dynamic fields
    // and how to solve it in a future seminar

    Student* ptr = &second;
    ptr->print(); // since this is a pointer-type, we access stuff with "->"
    (*ptr).print(); // EXACTLY the same idea, just written differently
    // ptr.print(); // ERROR: ptr is a pointer, not a Student object
    // !! IMPORTANT:
    // we use "." when we have an OBJECT
    // and "->" when we have a POINTER TO AN OBJECT
    // it DOESN'T MATTER whether the object itself was created using new!
    // the pointer can point to an ordinary local object too

    std::cout << "Name (borrowed pointer): " << second.getName() << std::endl;
    char* independentName = second.getNameCopy();
    independentName[0] = 'X';
    std::cout << "Independent copy: " << independentName << std::endl;
    std::cout << "Original name: " << second.getName() << std::endl; // unchanged!
    delete[] independentName; // WE own the new array returned by getNameCopy()
    independentName = nullptr;

    // however, if we are to do
    char* name = second.getName();
    name[0] = 'X';
    std::cout << "Original name now: " << second.getName() << std::endl; // changed!, which is very bad and we don't want that, so never do shallow-copies


    // destructors
    {
        Student shortLived("Temporary", 18);
        shortLived.print();
    } // destructor runs HERE, automatically!

    Student* dynamicStudent = new Student("Dynamic", 21);
    dynamicStudent->print();
    delete dynamicStudent; // destructor runs when we delete the dynamic object
    dynamicStudent = nullptr;

    // first and second will be destroyed automatically when main ends.
    // Destructors for local objects run in the reverse order of construction.
    return 0;
}
