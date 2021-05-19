// student ID: a1785394
// student name: Haoyu Wang


// create required classes
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

// define class
class Shape { 
	// define attributes
    private double width;
    private double height;
    private double radius;
    private double length;

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

public class Problem01 {
    public static void main(String[] args){

    	// Declare objects
    	Person person1 = new Person();
    	Person person2 = new Person("Haoyu","Wang",25,"China");
    	Shape shape1 = new Shape();
    	Shape shape2 = new Shape(1.1, 2.2, 3.3, 4.4);
    	Book book1 = new Book();
    	Book book2 = new Book("Java", 2020, "University", 500);
    	Animal animal1 = new Animal();
    	Animal animal2 = new Animal("a",20.5,"meat", 2);

    	// print information of objects by Accessors
    	System.out.println("person created by Parametric Constructor:");
    	person2.getGivenName();
    	person2.getLastName();
    	person2.getAge();
    	person2.getCityzenship();

    	System.out.println("person created by Basic Constructor:");
    	// Set information by Mutators
    	person1.setGivenName("Haoyu");
    	person1.setLastName("Wang");
    	person1.setAge(25);
    	person1.setCitizenship("China");

    	person1.getGivenName();
    	person1.getLastName();
    	person1.getAge();
    	person1.getCityzenship();
    	System.out.println();

    	System.out.println("Shape created by Parametric Constructor:");
    	shape2.getWidth();
    	shape2.getHeight();
    	shape2.getRadius();
    	shape2.getLength();
    	System.out.println();

    	System.out.println("Shape created by Basic Constructor:");
    	shape1.setWidth(5);
    	shape1.setHeight(6);
    	shape1.setRadius(7);
    	shape1.setLength(8);

    	shape1.getWidth();
    	shape1.getHeight();
    	shape1.getRadius();
    	shape1.getLength();
    	System.out.println();

    	System.out.println("Book created by Parametric Constructor:");
    	book2.getTitle();
    	book2.getYear();
    	book2.getPublish();
    	book2.getPages();

    	System.out.println("Book created by Basic Constructor:");
    	book1.setTitle("Python");
    	book1.setYear(2020);
    	book1.setPublish("College");
    	book1.setPages(400);

    	book1.getTitle();
    	book1.getYear();
    	book1.getPublish();
    	book1.getPages();
    	System.out.println();

    	System.out.println("animal created by Parametric Constructor:");
    	animal2.getName();
    	animal2.getWeight();
    	animal2.getFavouriteFood();
    	animal2.getAge();

    	System.out.println("animal created by Basic Constructor:");
    	animal1.setName("b");
    	animal1.setWeight(16.9);
    	animal1.setFavouriteFood("sugar");
    	animal1.setAge(5);

    	animal1.getName();
    	animal1.getWeight();
    	animal1.getFavouriteFood();
    	animal1.getAge();
    	System.out.println();
    }
}