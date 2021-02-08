// include LiteSQL's header file and generated header file
#include <iostream>
#include "litesql.hpp"
#include "exampledatabase.hpp"
// provide implementation for Person::sayHello
void example::Person::sayHello() {
  std::cout << "Hi! My name is " << name
  << " and I am " << age << " years old." << std::endl;
}

void example::user::sayHello() {
  std::cout << "Hi! My name is " << name << std::endl;
}

void example::ThingWithMethods::sayHello(std::string text,int UNUSED_ARG(repeat)) {
  std::cout << "Hi! I want to say :" << text << std::endl;
}


// no name collisions expected
using namespace litesql;
using namespace example;

int main(int UNUSED_ARG(argc), char ** UNUSED_ARG(argv)) {

  int exitcode=0;
  // using SQLite3 as backend
  ExampleDatabase db("mysql", "database=exampledb;user=root;port=3306;host=127.0.0.1;password=xfzhou@srls");
  try {
    // create tables, sequences and indexes
    db.verbose = true;

    if (db.needsUpgrade())
    {
      db.upgrade();
    }
    // start transaction
    db.begin();

    SelectQuery x;
    // create couple of Person-objects
    Person jeff(db);
    jeff.name = "Jeff";
    jeff.sex = Person::Sex::Male;
    jeff.age = 32;
    jeff.aDoubleValue = 0.32;
    Blob image_jeff("abc",4);
    jeff.image = image_jeff;
    // store Jeff to database
    try {
      jeff.update();
    } catch(ConstraintError& e) {
      cerr << e << endl;
    };
    Person jill(db);
    jill.name = "Jill";
    jill.sex = Person::Sex::Female;
    jill.image = Blob(NULL);
    jill.age = 33;
    jill.update();
    Person jack(db);
    jack.name = "Jack";
    jack.sex = Person::Sex::Male;
    jack.update();
    Person jess(db);
    jess.name = "Jess";
    jess.sex = Person::Sex::Female;
    jess.update();
    // build up relationships between Persons
    jeff.children().link(jack);
    jill.children().link(jack);
    jill.children().link(jess);
    jack.father().link(jeff);
    jack.mother().link(jill);
    jess.mother().link(jill);
    jack.siblings().link(jill);
    // roles (linking examples)
    Office office(db);
    office.update();
    School school(db);
    school.update();

    Employee jeffRole(db);
    jeffRole.update();
    jeff.roles().link(jeffRole);
    jeffRole.office().link(office);

    Student jackRole(db), jessRole(db);
    jackRole.update();
    jessRole.update();
    jack.roles().link(jackRole);
    jess.roles().link(jessRole);

    jackRole.school().link(school);
    jessRole.school().link(school);

    // count Persons
    cout << "There are " << select<Person>(db).count()
    << " persons." << endl;

    // select all Persons and order them by age
    vector<Person> family = select<Person>(db).orderBy(Person::Age).all();
    // show results
    for (vector<Person>::iterator i = family.begin(); i != family.end(); i++)
      cout << toString(*i) << endl;

    // XXX fix this for mysql
    // // select intersection of Jeff's and Jill's children and
    // // iterate results with cursor
    // Cursor<Person> cursor = intersect(jeff.children().get(),
    //                                   jill.children().get()).cursor();
    // // Jack should say hello
    // for (;cursor.rowsLeft();cursor++) 
    //   (*cursor).sayHello();

    // select a non-existing Person
    try {
      select<Person>(db, Person::Id == 100).one();
    } catch (NotFound e) {
      cout << "No Person with id 100" << endl;
    }
    // commit transaction
    db.commit();
    // clean up
    //        db.drop();
  } catch (Except& e) {
    cout << "Exception: \t" << std::endl;
    cout << e << endl;
    exitcode = 1;
  }
  return exitcode;
}
