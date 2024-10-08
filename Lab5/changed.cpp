#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include<limits>
using namespace std;

// Abstract base class for Zoo species
class Zoo_species
{
protected:
    string species_name;
    int species_count;

public:
 // Default constructor
    Zoo_species()
    {
        this->species_name = "";
        this->species_count = 0;
    }
    // Parameterized constructor
    Zoo_species(string name,int count)
    {
        this->species_name = name;
        this->species_count = count;
    }
     // Virtual destructor
    virtual ~Zoo_species()
    {
    }
    // Setters and getters for species_name and species_count
    void set_name(string name)
    {
        this->species_name = name;
    }
    void set_count(int count)
    {
        if (count <= 0)
        {
            cout << "Count must be greater than zero." << endl;
            return;
        }
        this->species_count = count;
    }
    string get_name()
    {
        return this->species_name;
    }
    int get_count()
    {
        return this->species_count;
    }
    // Pure virtual function for printing species information
    virtual void Print() const = 0;
     // Pure virtual function for retrieving species-specific details
    virtual string get_details() const = 0;
    // Virtual functions to determine the type of species
    virtual bool isMammal() const 
    { 
        return false; 
    }
    virtual bool isReptile() const 
    { 
        return false; 
    }
    virtual bool isBird() const 
    { 
        return false; 
    }
    virtual bool isAquatic() const 
    { 
        return false; 
    }
};
// Derived class for Mammal species
class Mammal : public Zoo_species
{
public:
    enum Diet_type
    {
        herbivore,
        carnivore
    };
private:
    Diet_type diet_type;
    static int mammalCount;

public:
// Default constructor
    Mammal()
    {
        mammalCount++;
    }
    // Parameterized constructor
    Mammal(string name, int count, Diet_type diet) : Zoo_species(name, count)
    {
        this->diet_type = diet;
        mammalCount++;
    }
    bool isMammal() const override
    {
        return true;
    }
    // Set the diet type for the mammal
    void set_diet(Diet_type diet)
    {
        this->diet_type = diet;
    }
    // Print function to display mammal information
    void Print() const override
    {
        string diet = "";
        if (diet_type == herbivore)
            diet = "herbivore";
        else
            diet = "carnivore";
        cout << this->species_name << " " << this->species_count << " " << diet << endl;
    }
    // Retrieve mammal-specific details
    string get_details() const override
    {
        if (diet_type == herbivore)
            return "herbivore";
        return "carnivore";
    }
    static int get_mammal_count()
    {
        return mammalCount;
    }
    ~Mammal()
    {
        mammalCount--;
    }
};
int Mammal::mammalCount = 0;
// Derived class for Reptile species
class Reptile : public Zoo_species
{
public:
    enum Feed_size
    {
        small,
        medium,
        large
    };

private:
    Feed_size feed_size;
    static int reptileCount;

public:
    // Default constructor
    Reptile()
    {
        reptileCount++;
    }
    // Parameterized constructor
    Reptile(string name, int count, Feed_size size) : Zoo_species(name, count)
    {
        this->feed_size = size;
        reptileCount++;
    }
    ~Reptile()
    {
        reptileCount--;
    }
    static int get_reptile_count()
    {
        return reptileCount;
    }
    // Reptile-specific function override
    bool isReptile() const override
    {
        return true;
    }
    // Set the feed size for the reptile
    void set_feed_size(Feed_size size)
    {
        this->feed_size = size;
    }
    // Print function to display reptile information
    void Print() const override
    {
        string feed = "";
        if (feed_size == small)
            feed = "small";
        else if (feed_size == medium)
            feed = "medium";
        else
            feed = "large";
        cout << species_name << " " << species_count << " " << feed << endl;
    }
    // Retrieve reptile-specific details
    string get_details() const override
    {
        if (feed_size == small)
            return "small";
        else if (feed_size == medium)
            return "medium";
        return "large";
    }
};
int Reptile::reptileCount = 0;
//Derived class for Bird species
class Bird : public Zoo_species
{
public:
    enum bird_feed_type
    {
        grain,
        insect,
        fish
    };
private:
    bird_feed_type Bird_feed;
    static int birdCount;
public:
    // Default constructor
    Bird()
    {
        birdCount++;
    }
    // Parameterized constructor
    Bird(string name, int count, bird_feed_type feed) : Zoo_species(name, count)
    {
        this->Bird_feed = feed;
        birdCount++;
    }
    // Bird-specific function override
    bool isBird() const override
    {
        return true;
    }
    // Set the bird feed type
    void set_bird_feed(bird_feed_type feed)
    {
        Bird_feed = feed;
    }
    // Print function to display bird information
    void Print() const override
    {
        string feed = "";
        if (Bird_feed == grain)
            feed = "grain";
        else if (Bird_feed == insect)
            feed = "insect";
        else
            feed = "fish";
        cout << species_name << " " << species_count << " " << feed << endl;
    }
    //Retrieve the bird specific details
    string get_details() const override
    {
        if (Bird_feed == grain)
            return "grain";
        else if (Bird_feed == insect)
            return "insect";
        else
            return "fish";
    }
    static int get_bird_count()
    {
        return birdCount;
    }
    ~Bird()
    {
        birdCount--;
    }
};
int Bird::birdCount = 0;

// Derived class for Aquatic species
class Aquatic : public Zoo_species
{
public:
    enum aqua_feed_type
    {
        fishfood,
        livefish,
        plants
    };
private:
    aqua_feed_type Aqua_feed;
    static int aquaticCount;
public:
    // Default constructor
    Aquatic()
    {
        aquaticCount++;
    }
    // Parameterized constructor
    Aquatic(string name, int count, aqua_feed_type feed) : Zoo_species(name, count)
    {
        this->Aqua_feed = feed;
        aquaticCount++;
    }
    // Aquatic-specific function override
    bool isAquatic() const override
    {
        return true;
    }
    // Set the aquatic feed type
    void set_aqua_feed(aqua_feed_type feed)
    {
        Aqua_feed = feed;
    }
    // Print function to display aquatic species information
    void Print() const override
    {
        string feed = "";
        if (Aqua_feed == fishfood)
            feed = "fishfood";
        else if (Aqua_feed == livefish)
            feed = "livefish";
        else
            feed = "plants";
        cout << species_name << " " << species_count << " " << feed << endl;
    }
    //Retrieve details about the aquatic species' feed type
    string get_details() const override
    {
        if (Aqua_feed == fishfood)
            return "fishfood";
        else if (Aqua_feed == livefish)
            return "livefish";
        return "plants";
    }
    static int get_aquatic_count()
    {
        return aquaticCount;
    }
    ~Aquatic()
    {
        aquaticCount--;
    }
};
int Aquatic::aquaticCount = 0;

vector<Zoo_species *> species_db;//List of all species
// Function to delete all species in the database
void delete_species_db()
{
    for (auto species : species_db)
    {
        delete species;
    }
    species_db.clear();
}

// Function to add a new species
void add_species(char category, string name, int count, string attribute)
{
    // Check if species already exists
    for (auto s : species_db)
    {
        if (s->get_name() == name)
        {
            if (s->get_details() == attribute)
            {   
                if(count<=0)
                {
                    cout << "Error: Count should be positive." << endl;
                    return;
                }
                s->set_count(s->get_count() + count);
                // cout<<"Successfully added"<<" " <<s->get_name()<<endl;//Increasing count if it is already present
                return;
            }
            else
            {
                cout << "Error: Attempt to add with different attribute." << endl;
                return;
            }
        }
    }
    // Create new species based on category
    Zoo_species *new_species = nullptr;
    if (category == 'M')
    {
        Mammal *mammal = new Mammal();
        mammal->set_name(name);
        mammal->set_count(count);
        if (attribute == "herbivore")
        {
            mammal->set_diet(Mammal::herbivore);
        }
        else if (attribute == "carnivore")
        {
            mammal->set_diet(Mammal::carnivore);
        }
        else
        {
            cout << "Error: Invalid diet type for mammal.Valid options are 'herbivore', 'carnivore'." << endl;
            return; 
        }
        // cout<<"Successfully added"<<" "<<mammal->get_name()<<endl;
        new_species = mammal;
    }
    else if (category == 'R')
    {
        Reptile *reptile = new Reptile();
        reptile->set_name(name);
        reptile->set_count(count);
        if (attribute == "small")
        {
            reptile->set_feed_size(Reptile::small);
        }
        else if (attribute == "medium")
        {
            reptile->set_feed_size(Reptile::medium);
        }
        else if (attribute == "large")
        {
            reptile->set_feed_size(Reptile::large);
        }
        else
        {
            cout << "Error: Invalid feed size for reptile. Valid options are 'small', 'medium', 'large'." << endl;
            return;
        }
        // cout<<"Successfully added"<<" "<<reptile->get_name()<<endl;
        new_species = reptile;
    }
    else if (category == 'B')
    {
        Bird *bird = new Bird();
        bird->set_name(name);
        bird->set_count(count);
        if (attribute == "grain")
        {
            bird->set_bird_feed(Bird::grain);
        }
        else if (attribute == "insect")
        {
            bird->set_bird_feed(Bird::insect);
        }
        else if (attribute == "fish")
        {
            bird->set_bird_feed(Bird::fish);
        }
        else
        {
            cout << "Error: Invalid bird feed type. Valid options are 'grain', 'insect', 'fish'." << endl;
            return;
        }
        // cout<<"Successfully added"<<" "<<bird->get_name()<<endl;
        new_species = bird;
    }
    else if (category == 'Q')
    {
        Aquatic *aquatic = new Aquatic();
        aquatic->set_name(name);
        aquatic->set_count(count);
        if (attribute == "fishfood")
        {
            aquatic->set_aqua_feed(Aquatic::fishfood);
        }
        else if (attribute == "livefish")
        {
            aquatic->set_aqua_feed(Aquatic::livefish);
        }
        else if (attribute == "plants")
        {
            aquatic->set_aqua_feed(Aquatic::plants);
        }
        else
        {
            cout << "Error: Invalid aquatic feed type. Valid options are 'fishfood', 'livefish', 'plants'." << endl;
            return;
        }
        // cout<<"Successfully added"<<" "<<aquatic->get_name()<<endl;
        new_species = aquatic;
    }
    else
    {
        cout << "Error: Invalid category.Valid options are 'M', 'R', 'B', 'Q'." << endl;
        return;
    }
    species_db.push_back(new_species);
}
//Delete the species under one catergory
void delete_species(char category, const string &name, int count)
{
    if(count<=0)
    {
        cout << "Error: Delete count cannot be negative or zero" << endl;
        return;
    }
    for (auto i = species_db.begin(); i!= species_db.end();i++)
    {
        Zoo_species *s = *i;
        if (s->get_name() == name)
        {
            if (s->get_count() < count)
            {
                cout << "Error: Delete count greater than existing count." << endl;
            }
            else if (s->get_count() == count)
            {
                delete s;
                species_db.erase(i);
            }
            else
            {
                s->set_count(s->get_count() - count);
            }
            // cout<<"Successfully deleted "<<s->get_name()<<endl;
            return;
        }
    }
    cout << "Error: Species not found." << endl;
}
//Show species 
void show_species(char category)
{
    // Output total species and individual counts
    if(category == 'A')
    {
        cout << "total species " << species_db.size() << endl;
        cout << "mammal " << Mammal::get_mammal_count() << endl;
        for(auto s : species_db)
        {
            if(s->isMammal())
            {
                s->Print();
            }
        }
        cout << "reptile " << Reptile::get_reptile_count() << endl;
        for (auto s : species_db)
        {
            if (s->isReptile())
            {
                s->Print();
            }
        }
        cout << "bird " << Bird::get_bird_count() << endl;
        for (auto s : species_db)
        {
            if (s->isBird())
            {
                s->Print();
            }
        }

        cout << "aquatic " << Aquatic::get_aquatic_count() << endl;
        for (auto s : species_db)
        {
            if (s->isAquatic())
            {
                s->Print();
            }
        }
    }
    else if(category == 'M')
    {
        cout<<"mammal "<<Mammal::get_mammal_count()<<endl;
        for(auto s : species_db)
        {
            if(s->isMammal())
            {
                s->Print();
            }
        }
    }
    else if(category == 'R')
    {
        cout << "reptile " << Reptile::get_reptile_count() << endl;
        for (auto s : species_db)
        {
            if (s->isReptile())
            {
                s->Print();
            }
        }
    }
    else if(category == 'B')
    {
        cout <<"bird "<<Bird::get_bird_count()<<endl;
        for (auto s : species_db)
        {
            if (s->isBird())
            {
                s->Print();
            }
        }
    }
    else if (category == 'Q')
    {
        cout<< "aquatic "<<Aquatic::get_aquatic_count()<<endl;
        for (auto s : species_db)
        {
            if (s->isAquatic())
            {
                s->Print();
            }
        }
    }
    else
    {
        cout<<category<<" is not a valid category."<<endl;
    }
}
void save_database(string filename)
{
    ofstream outfile(filename);
    if (!outfile)
    {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }
    int total_species = species_db.size();
    // Output total species and individual counts
    outfile << "total species " << total_species << endl;
    outfile << "mammal " << Mammal::get_mammal_count() << endl;
    // Save all mammals
    for (auto s : species_db)
    {
        if (s->isMammal())
        {
            outfile << s->get_name() << " " << s->get_count() << " " << s->get_details() << endl;
        }
    }
    outfile << "reptile " << Reptile::get_reptile_count() << endl;
    // Save all reptiles
    for (auto s : species_db)
    {
        if (s->isReptile())
        {
            outfile << s->get_name() << " " << s->get_count() << " " << s->get_details() << endl;
        }
    }
    outfile << "bird " << Bird::get_bird_count() << endl;
    // Save all birds
    for (auto s : species_db)
    {
        if (s->isBird())
        {
            outfile << s->get_name() << " " << s->get_count() << " " << s->get_details() << endl;
        }
    }
    outfile << "aquatic " << Aquatic::get_aquatic_count() << endl;
    // Save all aquatic species
    for (auto s : species_db)
    {
        if (s->isAquatic())
        {
            outfile << s->get_name() << " " << s->get_count() << " " << s->get_details() << endl;
        }
    }
    outfile.close();
}
void load_database(string filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        cout << "Error: Could not open " << filename << ". Starting with empty database." << endl;
        return;
    }
    string line;
    int total_species = 0, mammal_count = 0, reptile_count = 0, bird_count = 0, aquatic_count = 0;
    // Read total species count
    getline(infile, line);
    istringstream iss_total(line);
    iss_total >> line >> total_species;  // This is in the format "total species <count>"
    // Read and load mammals
    getline(infile, line);
    istringstream iss_mammal(line);
    iss_mammal >> line >> mammal_count;  //This is in the format "mammal <count>"
    for (int i = 0; i < mammal_count; i++)
    {
        string name, attribute;
        int count;
        getline(infile, line);
        istringstream iss(line);
        iss >> name >> count >> attribute;
        add_species('M', name, count, attribute);  // Adding mammal
    }
    // Read and load reptiles
    getline(infile, line);
    istringstream iss_reptile(line);
    iss_reptile >> line >> reptile_count;  // This is in the format "reptile <count>"
    for (int i = 0; i < reptile_count; i++)
    {
        string name, attribute;
        int count;
        getline(infile, line);
        istringstream iss(line);
        iss >> name >> count >> attribute;
        add_species('R', name, count, attribute);  // Adding reptile
    }
    // Read and load birds
    getline(infile, line);
    istringstream iss_bird(line);
    iss_bird >> line >> bird_count;  // this is in the format "bird <count>"
    for (int i = 0; i < bird_count; i++)
    {
        string name, attribute;
        int count;
        getline(infile, line);
        istringstream iss(line);
        iss >> name >> count >> attribute;
        add_species('B', name, count, attribute);  // Adding bird
    }
    // Read and load aquatic species
    getline(infile, line);
    istringstream iss_aquatic(line);
    iss_aquatic >> line >> aquatic_count;  //This is in the format  "aquatic <count>"
    for (int i = 0; i < aquatic_count; i++)
    {
        string name, attribute;
        int count;
        getline(infile, line);
        istringstream iss(line);
        iss >> name >> count >> attribute;
        add_species('Q', name, count, attribute);  // Adding aquatic species
    }
    infile.close();
}
int main()
{
    try
    {
        load_database("db.txt");
        string command;
        while (true)
        {
            cin >> command;
            if (command == "add")
            {
                char category;
                string name, attribute;
                int count;
                if (!(cin >> category >> name >> count >> attribute))
                {
                    cout << "Error: Invalid command format for 'add'. Expected format: add <category> <name> <count> <attribute>" << endl;
                    continue;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                add_species(category, name, count, attribute);
            }
            else if (command == "delete")
            {
                char category;
                string name;
                int count;
                if (!(cin >> category >> name >> count))
                {
                    cout << "Error: Invalid command format for 'delete'. Expected format: delete <category> <name> <count>" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    continue;
                }
                delete_species(category, name, count);
            }
            else if (command == "show")
            {
                char category;
                if (!(cin >> category))
                {
                    cout << "Error: Invalid command format for 'show'. Expected format: show <category>" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                show_species(category);
            }
            else if (command == "exit")
            {
                save_database("db.txt");
                break;
            }
            else
            {
                cout << "Error: Unknown command." << endl;
            }
        }
        delete_species_db();
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
