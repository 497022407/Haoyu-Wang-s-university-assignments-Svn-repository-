// student ID: a1785394
// student name: Haoyu Wang


// create required classes and subclasses
import java.util.ArrayList;


// define class
class Person { 
	// define attributes
    private String givenName;
    private String lastName;
    private int age;
    private String citizenship;

    // define Basic Constructor
    Person() { 
    	givenName = "unassigned";
    	lastName = "unassigned";
    	age = 0;
    	citizenship = "unassigned";
    }

    // Parametric Constructor
    Person(String givenName, String lastName, int age, String citizenship) {
    	this.givenName = givenName;
    	this.lastName = lastName;
    	this.age = age;
    	this.citizenship = citizenship;
    }

    // Mutators
    public void setGivenName(String name) {
    	givenName = name;
    }

    public void setLastName(String name) {
    	lastName = name;
    }

    public void setAge(int age) {
    	this.age = age;
    }

    public void setCitizenship(String citizenship) {
    	this.citizenship = citizenship;
    }

    // Accessors
    public String getGivenName() {
    	System.out.println("Given name: " + givenName);
    	return givenName;
    }

    public String getLastName() {
    	System.out.println("Last name: " + lastName);
    	return lastName;
    }

    public int getAge() {
    	System.out.println("Age: " + age);
    	return age;
    }

    public String getCityzenship() {
    	System.out.println("Cityzenship: " + citizenship);
    	return citizenship;
    }
}

// define subclass
class Student extends Person {

	// required attributes
	double[] marks = new double[4];
	String[] disciplines = new String[2];

	// required methods
	public double averageMarks() {

		double average = 0;
		double sum = 0;

		for(int i = 0; i < 3; i++){
			sum += marks[i];
		}

		average = sum / 4;

		System.out.println("average mark is " + average);

		return average;
	}

	public void displayDisciplines() {

		System.out.println("disciplines are " + disciplines[0] + " and " + disciplines[1]);

	}

	// define Basic Constructor
	Student () {

		for (int i = 0; i < 3; i++){
			marks[i] = 0;
		}

		disciplines[0] = "unassigned";
		disciplines[1] = "unassigned";
	}

	// Parametric Constructor
	Student (double[] marks, String[] disciplines) {

		this.marks = marks;
		this.disciplines = disciplines;
	}

	// Mutators
    public void setMarks(double[] marks) {
    	this.marks = marks;
    }

    public void setDisciplines(String[] disciplines) {
    	this.disciplines = disciplines;
    }

    // Accessors
    public double[] getMarks() {
    	System.out.println("marks: " + marks);
    	return marks;
    }

    public String[] getDisciplines() {
    	System.out.println("disciplines are " + disciplines[0] + " and " + disciplines[1]);
    	return disciplines;
    }
}

// define subclass
class Lecturer extends Person {

	// required attributes
	double salary;
	String[] disciplines = new String[2];

	// required methods
	public double annualSalary() {

		System.out.println("salary is " + salary);

		return salary;
	}

	public void displayDisciplines() {

		System.out.println("disciplines are " + disciplines[0] + " and " + disciplines[1]);

	}

	// define Basic Constructor
	Lecturer () {

		salary = 0;

		disciplines[0] = "unassigned";
		disciplines[1] = "unassigned";
	}

	// Parametric Constructor
	Lecturer (double salary, String[] disciplines) {

		this.salary = salary;
		this.disciplines = disciplines;
	}

	// Mutators
    public void setSalary(double salary) {
    	this.salary = salary;
    }

    public void setDisciplines(String[] disciplines) {
    	this.disciplines = disciplines;
    }

    // Accessors
    public double getSalary() {
    	System.out.println("salary: " + salary);
    	return salary;
    }

    public String[] getDisciplines() {
    	System.out.println("disciplines are " + disciplines[0] + " and " + disciplines[1]);
    	return disciplines;
    }
}

// define subclass
class Doctor extends Person {

	// required attributes
	String specialityl;

	// define Basic Constructor
	Doctor () {

		specialityl = "unassigned";

	}

	// Parametric Constructor
	Doctor (String specialityl) {

		this.specialityl = specialityl;
	}

	// Mutators
    public void setSpecialityl(String specialityl) {
    	this.specialityl = specialityl;
    }

    // Accessors
    public String getSpecialityl() {
    	System.out.println("specialityl: " + specialityl);
    	return specialityl;
    }
}

// define subclass
class Patient extends Person {

	// required attributes
	String diagnostic;
	String inTime;
	String prevTime;

	// define Basic Constructor
	Patient () {

		diagnostic = "unassigned";
		inTime = "unassigned";
		prevTime = "unassigned";

	}

	// Parametric Constructor
	Patient (String diagnostic, String inTime, String prevTime) {

		this.diagnostic = diagnostic;
		this.inTime = inTime;
		this.prevTime = prevTime;
	}

	// Mutators
    public void setDiagnostic(String diagnostic) {
    	this.diagnostic = diagnostic;
    }

    public void setInTime(String inTime) {
    	this.inTime = inTime;
    }

    public void setPrevTime(String prevTime) {
    	this.prevTime = prevTime;
    }

    // Accessors
    public String getDiagnostic() {
    	System.out.println("diagnostic: " + diagnostic);
    	return diagnostic;
    }

    public String getInTime() {
    	System.out.println("inTime: " + inTime);
    	return inTime;
    }

    public String getPrevTime() {
    	System.out.println("prevTime: " + prevTime);
    	return prevTime;
    }
}

// define class
class Shape { 
	// define attributes
    protected double width;
    protected double height;
    protected double radius;
    protected double length;

    // define Basic Constructor
    Shape() { 
    	width = 0;
    	height = 0;
    	radius = 0;
    	length = 0;
    }

    // Parametric Constructor
    Shape(double width, double height, double radius, double length) {
    	this.width = width;
    	this.height = height;
    	this.radius = radius;
    	this.length = length;
    }

    // Mutators
    public void setWidth(double width) {
    	this.width = width;
    }

    public void setHeight(double height) {
    	this.height = height;
    }

    public void setRadius(double radius) {
    	this.radius = radius;
    }

    public void setLength(double length) {
    	this.length = length;
    }

    // Accessors
    public double getWidth() {
    	System.out.println("Width: " + width);
    	return width;
    }

    public double getHeight() {
    	System.out.println("Height: " + height);
    	return height;
    }

    public double getRadius() {
    	System.out.println("Radius: " + radius);
    	return radius;
    }

    public double getLength() {
    	System.out.println("Length: " + length);
    	return length;
    }
}

// define subclass
class Rectangle extends Shape {

	Rectangle(){}

	// Parametric Constructor
	Rectangle(double width, double height, double length) {
    	this.width = width;
    	this.height = height;
    	this.length = length;
    }

    //methods required
    public double area() {
    	double area = width * height * length;

    	System.out.println("area: " + area);

    	return area;
    }
}

// define subclass
class Circle extends Shape {

	Circle(){}

	// Parametric Constructor
	Circle(double radius) {
    	this.radius = radius;
    }

    //methods required
    public double area() {
    	double area = radius * radius;

    	System.out.println("area: " + area);

    	return area;
    }
}

// define subclass
class Triangle extends Shape {

	Triangle(){}

	// Parametric Constructor
	Triangle(double width, double height) {
    	this.width = width;
    	this.height = height;
    }

    //methods required
    public double area() {
    	double area = width * height / 2;

    	System.out.println("area: " + area);

    	return area;
    }
}

// define class
class Book { 
	// define attributes
    private String title;
    private int year;
    private String publish;
    private int pages;

    // define Basic Constructor
    Book() { 
    	title = "unassigned";
    	year = 0;
    	publish = "unassigned";
    	pages = 0;
    }

    // Parametric Constructor
    Book(String title, int year, String publish, int pages) {
    	this.title = title;
    	this.year = year;
    	this.publish = publish;
    	this.pages = pages;
    }

    // Mutators
    public void setTitle(String title) {
    	this.title = title;
    }

    public void setYear(int year) {
    	this.year = year;
    }

    public void setPublish(String publish) {
    	this.publish = publish;
    }

    public void setPages(int pages) {
    	this.pages = pages;
    }

    // Accessors
    public String getTitle() {
    	System.out.println("Given name: " + title);
    	return title;
    }

    public int getYear() {
    	System.out.println("Last name: " + year);
    	return year;
    }

    public String getPublish() {
    	System.out.println("publish: " + publish);
    	return publish;
    }

    public int getPages() {
    	System.out.println("pages: " + pages);
    	return pages;
    }
}

// define subclass
class EBook extends Book {
	String url;
	EBook (){
		this.url = "unassigned";
	};
	EBook (String title, int year, String publish, int pages, String url) {
		super(title, year, publish, pages);

		this.url = url;
	}
	public void setUrl(String url) {
		this.url = url;
	}

	public String getUrl() {
		System.out.println("url: " + url);

		return url;
	}
}

// define subclass
class PhysicalBook extends Book {

	// define attributes
	int shelf;
	int aisle; 
	int floor;

	// basic constructor
	PhysicalBook (){
		this.shelf = 0;
		this.aisle = 0;
		this.floor = 0;
	};

	//Parametric constructor
	PhysicalBook (String title, int year, String publish, int pages, int shelf, int aisle, int floor) {
		super(title, year, publish, pages);

		this.shelf = shelf;
		this.aisle = aisle;
		this.floor = floor;
	}

	// Mutators
	public void setShelf(int shelf) {
		this.shelf = shelf;
	}

	public void setAisle(int aisle) {
		this.aisle = aisle;
	}

	public void setFloor(int floor) {
		this.floor = floor;
	}

	// Accessors
	public int getShelf() {
		System.out.println("shelf: " + shelf);

		return shelf;
	}

	public int getAisle() {
		System.out.println("aisle: " + aisle);

		return aisle;
	}

	public int getFloor() {
		System.out.println("floor: " + floor);

		return floor;
	}

	// required methods
	public void displayBookLocation() {
		System.out.println("shelf: " + shelf);
		System.out.println("aisle: " + aisle);
		System.out.println("floor: " + floor);
	}
}

// define class
class Animal { 
	// define attributes
    private String name;
    private double weight;
    private String favouriteFood;
    private int age;

    // define Basic Constructor
    Animal() { 
    	name = "unassigned";
    	weight = 0;
    	favouriteFood = "unassigned";
    	age = 0;
    }

    // Parametric Constructor
    Animal(String name, double weight, String favouriteFood, int age) {
    	this.name = name;
    	this.weight = weight;
    	this.favouriteFood = favouriteFood;
    	this.age = age;
    }

    // Mutators
    public void setName(String name) {
    	this.name = name;
    }

    public void setWeight(double weight) {
    	this.weight = weight;
    }

    public void setFavouriteFood(String favouriteFood) {
    	this.favouriteFood = favouriteFood;
    }

    public void setAge(int age) {
    	this.age = age;
    }

    // Accessors
    public String getName() {
    	System.out.println("Given name: " + name);
    	return name;
    }

    public double getWeight() {
    	System.out.println("Last name: " + weight);
    	return weight;
    }

    public String getFavouriteFood() {
    	System.out.println("favouriteFood: " + favouriteFood);
    	return favouriteFood;
    }

    public int getAge() {
    	System.out.println("age: " + age);
    	return age;
    }
}

// define subclass
class Lion extends Animal {

	// basic constructor
	Lion() {};

	// Parametric Constructor
	Lion(String name, double weight, String favouriteFood, int age) {
		super(name, weight, favouriteFood, age);
	}

	// method required
	public void makeSound(){
		System.out.println("sound: AAAAAA");
	}
}

// define subclass
class Turtle extends Animal {

	// basic constructor
	Turtle() {};

	// Parametric Constructor
	Turtle(String name, double weight, String favouriteFood, int age) {
		super(name, weight, favouriteFood, age);
	}

	// method required
	public void makeSound(){
		System.out.println("sound: .......");
	}
}

// define subclass
class Chameleon extends Animal {

	// basic constructor
	Chameleon() {};

	// Parametric Constructor
	Chameleon(String name, double weight, String favouriteFood, int age) {
		super(name, weight, favouriteFood, age);
	}

	// method required
	public void makeSound(){
		System.out.println("sound: OOOOOO");
	}
}

public class Problem02 {
    public static void main(String[] args){

    	double [] marks = {100,70,80,90};
    	String [] disciplines = {"Computer Science", "Media"};

    	// Declare objects
    	Student student1 = new Student();
    	Student student2 = new Student(marks,disciplines);
    	Lecturer lecturer1 = new Lecturer();
    	Lecturer lecturer2 = new Lecturer(4000, disciplines);
    	Doctor doctor1 = new Doctor();
    	Doctor doctor2 = new Doctor("head");
    	Patient patient1 = new Patient();
    	Patient patient2 = new Patient("flu", "inTime", "prevTime");

    	Rectangle rectangle1 = new Rectangle();
    	Rectangle rectangle2 = new Rectangle(1,2,3);
    	Circle circle1 = new Circle();
    	Circle circle2 = new Circle(2);
    	Triangle triangle1 = new Triangle();
    	Triangle triangle2 = new Triangle(1,2);

    	EBook eBook1 = new EBook();
    	EBook eBook2 = new EBook("Java", 2020, "University", 500, "www.google.com");
    	PhysicalBook physicalBook1 = new PhysicalBook();
    	PhysicalBook physicalBook2 = new PhysicalBook("Java", 2020, "University", 500, 4, 5, 6);

    	Lion lion1 = new Lion();
    	Lion lion2 = new Lion("lion2",10.5,"meat", 1);
    	Turtle turtle1 = new Turtle();
    	Turtle turtle2 = new Turtle("turtle2",17.2,"meat", 16);
    	Chameleon chameleon1 = new Chameleon();
    	Chameleon chameleon2 = new Chameleon("chameleon2",8.1,"meat", 6);

    	// print information of objects by Accessors
    	System.out.println("student created by Parametric Constructor:");
    	student2.averageMarks();
    	student2.displayDisciplines();
    	
    	System.out.println("student created by Basic Constructor:");
    	// Set information by Mutators
    	student1.setMarks (marks);
    	student1.setDisciplines (disciplines);
    	student1.averageMarks();
    	student1.displayDisciplines();
    	System.out.println();   	

    	// print information of objects by Accessors
    	System.out.println("lecturer created by Parametric Constructor:");
    	lecturer2.annualSalary();
    	lecturer2.displayDisciplines();
    	
    	System.out.println("lecturer created by Basic Constructor:");
    	// Set information by Mutators
    	lecturer1.setSalary (5000);
    	lecturer1.setDisciplines (disciplines);
    	lecturer1.annualSalary();
    	lecturer1.displayDisciplines();
    	System.out.println();   

    	// print information of objects by Accessors
    	System.out.println("doctor created by Parametric Constructor:");
    	doctor2.getSpecialityl();
    	
    	System.out.println("doctor created by Basic Constructor:");
    	// Set information by Mutators
    	doctor1.setSpecialityl ("head");
    	doctor1.getSpecialityl();
    	System.out.println(); 	

    	// print information of objects by Accessors
    	System.out.println("patient created by Parametric Constructor:");
    	patient2.getDiagnostic();
    	
    	System.out.println("patient created by Basic Constructor:");
    	// Set information by Mutators
    	patient1.setDiagnostic ("head");
    	patient1.getDiagnostic();
    	System.out.println(); 

    	// print information of objects by Accessors
    	System.out.println("rectangle created by Parametric Constructor:");
    	rectangle2.getWidth();
    	rectangle2.getHeight();
    	rectangle2.getLength();
    	rectangle2.area();
    	System.out.println();
    	
    	System.out.println("rectangle created by Basic Constructor:");
    	// Set information by Mutators
		rectangle1.setWidth(4);
    	rectangle1.setHeight(5);
    	rectangle1.setLength(6);

    	rectangle1.getWidth();
    	rectangle1.getHeight();
    	rectangle1.getLength();
    	rectangle1.area();
    	System.out.println(); 

    	// print information of objects by Accessors
    	System.out.println("circle created by Parametric Constructor:");
    	circle2.getRadius();
    	circle2.area();
    	System.out.println();

    	System.out.println("circle created by Basic Constructor:");
    	// Set information by Mutators
		circle1.setRadius(3);

    	circle1.getRadius();
    	circle1.area();
    	System.out.println(); 

    	// print information of objects by Accessors
    	System.out.println("triangle created by Parametric Constructor:");
    	triangle2.getHeight();
    	triangle2.getWidth();
    	triangle2.area();
    	System.out.println();

    	System.out.println("triangle created by Basic Constructor:");
    	// Set information by Mutators
		triangle1.setHeight(3);
		triangle1.setWidth(4);

    	triangle1.getHeight();
    	triangle1.getWidth();
    	triangle1.area();
    	System.out.println(); 

    	System.out.println("EBook created by Parametric Constructor:");
    	eBook2.getTitle();
    	eBook2.getYear();
    	eBook2.getPublish();
    	eBook2.getPages();
    	eBook2.getUrl();
    	System.out.println(); 

    	System.out.println("EBook created by Basic Constructor:");
    	eBook1.setTitle("Python");
    	eBook1.setYear(2020);
    	eBook1.setPublish("College");
    	eBook1.setPages(400);
    	eBook1.setUrl("www.adelaide.com");

    	eBook1.getTitle();
    	eBook1.getYear();
    	eBook1.getPublish();
    	eBook1.getPages();
    	eBook1.getUrl();
    	System.out.println();

    	System.out.println("PhysicalBook created by Parametric Constructor:");
    	physicalBook2.getTitle();
    	physicalBook2.getYear();
    	physicalBook2.getPublish();
    	physicalBook2.getPages();
    	physicalBook2.displayBookLocation();
    	System.out.println();

    	System.out.println("PhysicalBook created by Basic Constructor:");
    	physicalBook1.setTitle("Python");
    	physicalBook1.setYear(2020);
    	physicalBook1.setPublish("College");
    	physicalBook1.setPages(400);
    	physicalBook1.setShelf(10);
    	physicalBook1.setAisle(20);
    	physicalBook1.setFloor(30);


    	physicalBook1.getTitle();
    	physicalBook1.getYear();
    	physicalBook1.getPublish();
    	physicalBook1.getPages();
    	physicalBook1.displayBookLocation();
    	System.out.println();

    	System.out.println("lion created by Parametric Constructor:");
    	lion2.getName();
    	lion2.getWeight();
    	lion2.getFavouriteFood();
    	lion2.getAge();
    	lion2.makeSound();

    	System.out.println("lion created by Basic Constructor:");
    	lion1.setName("lion1");
    	lion1.setWeight(16.9);
    	lion1.setFavouriteFood("sugar");
    	lion1.setAge(5);

    	lion1.getName();
    	lion1.getWeight();
    	lion1.getFavouriteFood();
    	lion1.getAge();
    	lion1.makeSound();
    	System.out.println();

    	System.out.println("turtle created by Parametric Constructor:");
    	turtle2.getName();
    	turtle2.getWeight();
    	turtle2.getFavouriteFood();
    	turtle2.getAge();
    	turtle2.makeSound();

    	System.out.println("turtle created by Basic Constructor:");
    	turtle1.setName("turtle1");
    	turtle1.setWeight(12);
    	turtle1.setFavouriteFood("fish");
    	turtle1.setAge(23);

    	turtle1.getName();
    	turtle1.getWeight();
    	turtle1.getFavouriteFood();
    	turtle1.getAge();
    	turtle1.makeSound();
    	System.out.println();

    	System.out.println("chameleon created by Parametric Constructor:");
    	chameleon2.getName();
    	chameleon2.getWeight();
    	chameleon2.getFavouriteFood();
    	chameleon2.getAge();
    	chameleon2.makeSound();

    	System.out.println("chameleon created by Basic Constructor:");
    	chameleon1.setName("chameleon1");
    	chameleon1.setWeight(20);
    	chameleon1.setFavouriteFood("fresh meat");
    	chameleon1.setAge(2);

    	chameleon1.getName();
    	chameleon1.getWeight();
    	chameleon1.getFavouriteFood();
    	chameleon1.getAge();
    	chameleon1.makeSound();
    	System.out.println();
    }
}