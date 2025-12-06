
/*
fn es_01(){
    // Test 1: i32
    println!("--- Test: i32 ---");
    let n = 42;
    print(&n);

    // Test 2: String
    println!("\n--- Test: String ---");
    let s = String::from("Hello World");
    print(&s);

    // Test 3: Vec<i32>
    println!("\n--- Test: Vec<i32> ---");
    let numbers = vec![1, 2, 3];
    print(&numbers);

    // Test 4: Vec<String>
    println!("\n--- Test: Vec<String> ---");
    let words = vec![
        String::from("uno"),
        String::from("due"),
        String::from("tre"),
    ];
    print(&words);

    // Test 5: Vec<Vec<i32>>
    println!("\n--- Test: Vec<Vec<i32>> ---");
    let matrix = vec![vec![1, 2], vec![3, 4]];
    print(&matrix);

    // Test 6: Mixed deep structure
    println!("\n--- Test: Vec<Vec<String>> ---");
    let nested_strings = vec![
        vec![String::from("a"), String::from("b")],
        vec![String::from("c")],
    ];
    print(&nested_strings);
}
trait Printable{
    fn print(&self);
}
impl Printable for i32{
    fn print(&self){
        println!("Int: {}", self);
    }
}
impl Printable for String{
    fn print(&self){
        println!("String: {}", self);
    }
}
impl<T:Printable> Printable for Vec<T>{
    fn print(&self){
        println!("Vec: ");
        for item in self{
            item.print();
        }
    }
}
fn print<T>(arg: &T) where T:Printable{
    arg.print();
}
*/

/*
use rand::{rng, thread_rng};
use rand::prelude::IndexedRandom;
use crate::Category::Science;

fn es_02(){}
#[derive(Debug, Default)]
enum Category {
    #[default]
    Fantasy,
    Horror,
    Romance,
    SciFi,
    History,
}
#[derive(Debug)]
struct Book<'a>{
    title: &'a str,
    cat: Category
}
#[derive(Debug, Default)]
struct Library<'a>{
    bookcases: [Vec<Book<'a>>;10]
}
impl<'a> Default for Book<'a> {
    fn default() -> Self {
        let titles = [
        "The Wind Gate",
        "Moon Tower",
        "Lost Empire",
        "Silent Shadows",
        "Fire Path",
        ];

        let mut rng = rng();

        Book {title: titles.choose(&mut rng).unwrap(), cat: Category::default()}
    }
}
impl<'a> Book<'a> {
    fn default_with_cat(cat: Category) -> Self{
        Self{cat, ..Default::default()}
    }
}
trait Populatable{
    fn populate(&mut self);
}
impl<'a> Populatable for Library<'a>{
    fn populate(&mut self){
        self.bookcases.iter_mut().for_each(|bookcase| {for _ in 0..3 {bookcase.push(Book::default());}})
    }
}
*/

/*
use std::fmt::{Debug, Display};

fn es_03(){}
fn restricted<T:Debug+Ord,U:Display>(t1:T,t2:T,u:U) -> T{
    let min_value = if t1 < t2 { t1 } else { t2 };
    println!("minor: {:?}\nu: {}\n", min_value, u);
    min_value
}
*/

/*
fn es_04(){
    // Creazione dei task
    let task1 = Task::new("Comprare il latte".to_string(), 1);
    let task2 = Task::new("Studiare Rust".to_string(), 3);
    let mut task3 = Task::new("Fare esercizio".to_string(), 2);
    task3.done = true; // segniamo questo task come completato

    // Creazione del contenitore Tasks
    let mut tasks = Tasks::new();
    tasks.add_task(task1);
    tasks.add_task(task2);
    tasks.add_task(task3);

    // Iterazione manuale con next()
    println!("Task non completati:");
    while let Some(task) = tasks.next() {
        println!("{} (priorità {})", task.name, task.priority);
    }

    // Alla fine, tasks sarà vuoto
    println!("\nStato finale del contenitore Tasks: {:?}", tasks);
}
#[derive(Debug)]
struct Task{
    name : String,
    priority: i32,
    done : bool
}
#[derive(Debug)]
struct Tasks{
    tasks : Vec<Task>
}
impl Task{
    fn new(name: String, priority: i32) -> Task{
        Task{name, priority, done: false}
    }
}
impl Tasks{
    fn new() -> Tasks{
        Tasks{tasks: Vec::new()}
    }
    fn add_task(&mut self, task: Task){
        self.tasks.push(task);
    }
}
impl Iterator for Tasks{
    type Item = Task;
    fn next(&mut self) -> Option<Self::Item>{
        while !self.tasks.is_empty() {
            let task = self.tasks.remove(0);
            if(!task.done) {
                return Some(task);
            }
        }
        None
    }
}
*/

/*
use std::ops::{Add, AddAssign};

fn es_05(){
    let p1 = Pair(10, "Hello".to_string());
    let p2 = Pair(3, "World".to_string());

    // Pair + i32
    let r1 = p1 + 5;
    println!("Pair + i32: ({}, {})", r1.0, r1.1);

    // Pair - i32
    let p3 = Pair(10, "Hello".to_string());
    let r2 = p3 - 3;
    println!("Pair - i32: ({}, {})", r2.0, r2.1);

    // Pair + &str
    let p4 = Pair(5, "Hi".to_string());
    let r3 = p4 + " there";
    println!("Pair + &str: ({}, {})", r3.0, r3.1);

    // Pair - &str
    let p5 = Pair(5, "Hello world".to_string());
    let r4 = p5 - "world";
    println!("Pair - &str: ({}, {})", r4.0, r4.1);

    // Pair + Pair
    let p6 = Pair(2, "A".to_string());
    let p7 = Pair(3, "B".to_string());
    let r5 = p6 + p7;
    println!("Pair + Pair: ({}, {})", r5.0, r5.1);

    // Pair - Pair
    let p8 = Pair(10, "foobar".to_string());
    let p9 = Pair(3, "bar".to_string());
    let r6 = p8 - p9;
    println!("Pair - Pair: ({}, {})", r6.0, r6.1);

    // Pair * i32
    let p10 = Pair(2, "xy".to_string());
    let r7 = p10 * 3;
    println!("Pair * i32: ({}, {})", r7.0, r7.1);
}
struct Pair(i32, String);
impl std::ops::Add<i32> for Pair{
    type Output = Pair;
    fn add(self, rhs: i32) -> Self::Output {
        Pair{0:self.0+rhs,1:self.1}
    }
}
impl std::ops::Sub<i32> for Pair{
    type Output = Pair;
    fn sub(self, rhs: i32) -> Self::Output {
        Pair{0:self.0-rhs,1:self.1}
    }
}
impl std::ops::Add<&str> for Pair{
    type Output = Pair;
    fn add(self, rhs: &str) -> Self::Output {
        Pair{0:self.0,1:self.1.chars().chain(rhs.chars()).collect()}
    }
}
impl std::ops::Sub<&str> for Pair{
    type Output = Pair;
    fn sub(self, rhs: &str) -> Self::Output {
        Pair{0:self.0,1:self.1.replace(rhs,"")}
    }
}
impl std::ops::Add for Pair{
    type Output = Pair;
    fn add(self, rhs: Pair) -> Self::Output {
        Pair{0:self.0+rhs.0, 1:self.1.chars().chain(rhs.1.chars()).collect()}
    }
}
impl std::ops::Sub for Pair{
    type Output = Pair;
    fn sub(self, rhs: Pair) -> Self::Output {
        Pair{0:self.0-rhs.0, 1:self.1.replace(rhs.1.as_str(),"")}
    }
}
impl std::ops::Mul<i32> for Pair{
    type Output = Pair;
    fn mul(self, rhs: i32) -> Self::Output {
        Pair{0:self.0.pow(rhs as u32),1:self.1.repeat(rhs as usize)}
    }
}
*/


fn main() {
    //es_01();
    //es_02();
    //es_03();
    //es_04()
    //es_05();
    
}
