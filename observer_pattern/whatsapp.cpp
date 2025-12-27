#include<bits/stdc++.h>
using namespace std;

// 1.observer interface
class IObserver{
    public:
    virtual void update(string message)=0;
    virtual ~IObserver(){}

};

//2.The subject 
class ISubject{
    public:
    virtual void attach(IObserver* observer)=0;
    virtual void detach(IObserver* observer)=0;
    virtual void notify()=0;
    virtual ~ISubject(){}

};

//3. The concrete subject class(UserGroup)

class GroupChat:public ISubject{
    private:
    // maintains a list of observers
    vector<IObserver*>observers;
    string message;
    public:
    // the attach function
    void attach(IObserver* obs) override{
        observers.push_back(obs);
    }
    //the detach function
    void detach(IObserver* obs)override{
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }
    // notify function
    void notify() override{
        for(IObserver* obs:observers){
            obs->update(message);
        }
    }

    void addMessage(string message){
        this->message=message;
        notify();
    }

};

//4. Concerte Observer

class User:public IObserver{
    private:
    string name;
    public:
    User(string name):name(name){}
    void update(string message){
        cout<<name<<" recieved: "<<message<<endl;
    }
};

int main(){
    GroupChat* whatsapp=new GroupChat();
    User* user1=new User("Shubham");
    User* user2=new User("India");

    // attach the observers to the subject
    whatsapp->attach(user1);
    whatsapp->attach(user2);

    // event happens

    whatsapp->addMessage("Hello Everyone!");

    // detach one user

    whatsapp->detach(user2);

    // again let the event happen

    whatsapp->addMessage("Nice Weather!");

    delete whatsapp;
    delete user1;
    delete user2;
    return 0;

}