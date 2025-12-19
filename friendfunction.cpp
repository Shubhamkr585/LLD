A friend function is used when a non-member function requires special access to the private or protected members of a class. Here are two primary scenarios where this is necessary.

1. Operator overloading
2. For accessing private and protected members of a class.



## 1. Overloading Operators ↔️
This is the most common use case for friend functions, especially for binary operators where your class is the right-hand operand.

Scenario: You want to overload the stream insertion operator << to allow easy printing of your object's state, like std::cout << myObject;.

Problem: The operator<< function must take the std::ostream object as its first (left-hand) parameter. Because member functions always have the class instance (this) as their implicit first parameter, this operator cannot be a member function of your class.

Solution: You must implement it as a non-member function. However, this function needs to access the private members of your object to print them. By declaring operator<< as a friend inside your class, you grant it this special access.