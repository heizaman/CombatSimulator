#include <iostream>
#include <ctime>
#include <random>

using namespace std;




//We first created 2 classes storing the properties of humans and demons respectively

//There are 2 friend functions of these classes
//They first determine if an attack is successful or not
//If the attack is successful, they calculate the remaining health of the attacked creature
//If the health is negative, a different int return value indicates to delete(kill) that creature and send in the next one

class demons;

class humans {
    //A good programming practice is to start the names of the private variables with an _
    //This helps us to easily determine what is private and what is not
    //I have not followed this in this program, but will do in all further programs
    static int totalhumans;
    static int humansleft;
    //Used static as they are common for all objects of the class
    int health;
    int damage;
    float attackchance;

public:
    humans() {
        health = 100;
        damage = 30;
        attackchance = 0.6f;
    }

    void resetHealth() {
        health = 100;
    }

    static void setTotalInitial() {
        //Input from user for number of humans
        cout << "Enter the number of humans: ";
        cin >> totalhumans;
        humansleft = totalhumans;
    }

    static int getleft() {
        return humansleft;
    }

    static int gettotal() {
        return totalhumans;
    }

    static void decrementleft(int i = 1) {
        humansleft -= i;
    }

    int getHealth() {
        return health;
    }

    int getDamage() {
        return damage;
    }

    float getAttackchance() {
        return attackchance;
    }

    void setHealth(int newhealth) {
        health = newhealth;
    }

    friend void demonAttHuman(humans *h, demons *d, float chance);
    friend void humanAttDemon(humans *h, demons *d, float chance);
};

int humans::totalhumans;
int humans::humansleft;

class demons {
    static int totaldemons;
    static int demonsleft;
    //Used static as they are common for all objects of the class
    int health;
    int damage;
    float attackchance;

public:
    demons() {
        health = 80;
        damage = 20;
        attackchance = 0.4f;
    }

    void resetHealth() {
        health = 80;
    }


    static void setTotalInitial() {
        //Input from user for number of demons
        cout << "Enter the number of demons: ";
        cin >> totaldemons;
        demonsleft = totaldemons;
    }

    static int getleft() {
        return demonsleft;
    }

    static int gettotal() {
        return totaldemons;
    }

    static void decrementleft(int i = 1) {
        demonsleft -= i;
    }

    int getHealth() {
        return health;
    }

    int getDamage() {
        return damage;
    }

    float getAttackchance() {
        return attackchance;
    }

    void setHealth(int newhealth) {
        health = newhealth;
    }

    friend void demonAttHuman(humans *h, demons *d, float chance);
    friend void humanAttDemon(humans *h, demons *d, float chance);
};

int demons::totaldemons;
int demons::demonsleft;

//For a demon attacking a human
void demonAttHuman(humans *h, demons *d, float chance) {
    if(chance <= d->getAttackchance()) {
        return;   //missed
    }

    h->setHealth(h->getHealth() - d->getDamage());

    if(h->getHealth() <= 0) {
        //killed
        //reset health to full as it is a new human
        //decrement the number of humans left
        h->resetHealth();
        h->decrementleft();
    }

    //damaged
}

//For a human attacking a demon
void humanAttDemon(humans *h, demons *d, float chance) {
    if(chance <= h->getAttackchance()) {
        return;   //missed
    }

    d->setHealth(d->getHealth() - h->getDamage());

    if(d->getHealth() <= 0) {
        //killed
        //reset health to full as it is a new demon
        //decrement the number of demons left
        d->resetHealth();
        d->decrementleft();
    }

    //damaged
}




void printresult();
void simulate();




int main()
{
    cout << "WELCOME TO HUMANS vs DEMONS!!" << endl << endl;

    //Set static variables that store number of humans and number of demons
    humans::setTotalInitial();
    demons::setTotalInitial();

    simulate();

    printresult();

    return 0;
}




void printresult() {
    cout << endl << "Humans left: " << humans::getleft() << endl;
    cout << "Demons left: " << demons::getleft() << endl;

    cout << endl << "Humans killed: " << humans::gettotal()-humans::getleft() << endl;
    cout << "Demons killed: " << demons::gettotal()-demons::getleft() << endl << endl;

    (humans::getleft()>demons::getleft()) ? cout << "Humans won!" : cout << "Demons won!";

}

void simulate() {
    //A random number generator with time seed
    static default_random_engine randomGenerator(time(NULL));
    //A randomly generated float between 0.0 and 1.0
    static uniform_real_distribution<float> randomfloat(0.0f, 1.0f);
    //Made them static as they should be made only once in the program

    //A boolean to keep track of whose turn to attack it is
    bool humanTurn = true;

    //Creating initial human and demon
    humans *h = new humans();
    demons *d = new demons();

    while(humans::getleft()>0 && demons::getleft()>0) {
        //Random probability of a hit to compare with the attackchance
        float prob = randomfloat(randomGenerator);

        if(humanTurn)
            humanAttDemon(h, d, prob);
        else
            demonAttHuman(h, d, prob);

        //Swap turn
        humanTurn = !humanTurn;
    }

    delete h;
    delete d;
}
