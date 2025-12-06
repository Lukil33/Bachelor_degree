use std::collections::LinkedList;
use std::fmt::{Display, Formatter};
use std::ops::{Add, Sub};
use rand::Rng;

/*
fn es_01(){
    let s = lucky_slice("hello world");
    println!("{:?}", s);
}
fn find_equal<'a,'b>(s1: &'a str, s2: &'b str) -> Option<(&'a str, &'b str)>{
    let b1 = s1.as_bytes();
    let b2 = s2.as_bytes();

    if b1.len() < 2 || b2.len() < 2 {
        return None;
    }

    for i in 0..b1.len()-1{
        for j in 0..b2.len()-1{
            if b1[i..=i+1] == b2[j..=j+1]{
                return Some((&s1[i..=i+1], &s2[j..=j+1]));
            }
        }
    }
    None
}
fn lucky_slice(input_str: &str) -> Option<&str>{
    let mut s = String::with_capacity(input_str.len());
    for _ in 0..input_str.len(){
        s.push(rand::rng().random_range('a'..='z'));
    }
    println!("check: {} - {}", input_str, s);
    Some(find_equal(input_str, &s)?.0)
}
*/

/*
fn es_02(){
    // Creiamo la famiglia
    let grandpa = Person::new("Grandpa".to_string(), None, None);
    let grandma = Person::new("Grandma".to_string(), None, None);

    let father = Person::new("Father".to_string(), Some(&grandpa), Some(&grandma));
    let mother = Person::new("Mother".to_string(), None, None);

    let child = Person::new("Child".to_string(), Some(&father), Some(&mother));

    // Test find_relatives
    let relatives_0 = child.find_relatives(0);
    println!("Generations 0:");
    for r in &relatives_0 {
        println!("{}", r.name);
    }

    let relatives_1 = child.find_relatives(1);
    println!("\nGenerations 1:");
    for r in &relatives_1 {
        println!("{}", r.name);
    }

    let relatives_2 = child.find_relatives(2);
    println!("\nGenerations 2:");
    for r in &relatives_2 {
        println!("{}", r.name);
    }

    // Test find_root
    let roots = child.find_root();
    println!("\nRoots:");
    for r in &roots {
        println!("{}", r.name);
    }
}
struct Person<'a> {
    name: String,
    father: Option<&'a Person<'a>>,
    mother: Option<&'a Person<'a>>
}

impl<'a> Person<'a>{
    fn new(name: String, father: Option<&'a Person>, mother: Option<&'a Person>) -> Person<'a>{
        Person{name, father, mother}
    }
    fn find_relatives(&self, generations: u32) -> Vec<&Person<'a>>{
        let mut v = Vec::new();
        v.push(self);
        if generations > 0{
            if(self.father.is_some()){
                v.append(&mut self.father.unwrap().find_relatives(generations-1));
            }
            if(self.mother.is_some()){
                v.append(&mut self.mother.unwrap().find_relatives(generations-1));
            }
        }
        v
    }
    fn find_root(&self) -> Vec<&Person<'a>>{
        let mut v = Vec::new();
        if self.father.is_none() || self.mother.is_none() {
            v.push(self);
        }
        if(self.father.is_some()){
            v.append(&mut self.father.unwrap().find_root());
        }
        if(self.mother.is_some()){
            v.append(&mut self.mother.unwrap().find_root());
        }
        v
    }
}
*/

/*
fn es_03(){
    let i = ImportantExcerpt { part: "life is short, you need rust" };
    let j = i.announce_and_return_part("hello");
    println!("j: {}", j);
}
struct ImportantExcerpt<'a> {
    part: &'a str,
}
impl<'a:'b, 'b> ImportantExcerpt<'a> { //THIS LINE
    fn announce_and_return_part(&'a self, announcement: &'b str) -> &'b str {
        println!("Attention please: {}", announcement);
        self.part
    }
}
*/

/*
fn es_04(){
    let d = DoubleRef { r: &5, s: &3 };
    println!("d.r: {}, d.s: {}", d.r, d.s);
}
struct DoubleRef<'a:'b,'b,T> {
    r: &'b T,
    s: &'a T
}
*/

/*
fn es_05(){
    let mut v = vec![1,2,3,4,5];
    let (left, right) = v.split_at_mut(3);
    println!("left: {:?}, right: {:?}", left, right);
}
trait Split<'a, ReturnType>{
    fn split(&'a self) -> (ReturnType, ReturnType);
}
impl<'a,> Split<'a, &'a str> for String {
    fn split(&'a self) -> (&'a str, &'a str) {
        let mid = self.len() / 2;
        (&self[..mid], &self[mid..])
    }
}
impl<'a,> Split<'a, &'a[i32]> for &[i32] {
    fn split(&'a self) -> (&'a[i32], &'a[i32]) {
        let mid = self.len() / 2;
        (&self[..mid], &self[mid..])
    }
}
impl<'a,> Split<'a, LinkedList<f64>> for LinkedList<f64> {
    fn split(&'a self) -> (LinkedList<f64>, LinkedList<f64>) {
        let mut left = LinkedList::new();
        let mut right = LinkedList::new();
        for (a,&b) in self.iter().enumerate(){
            if a > self.len()/2{
                right.push_back(b);
            }else{
                left.push_back(b);
            }
        }
        (left, right)
    }
}
*/

/*
fn es_06(){
    // --- Test Default ---
    let p = Point::default();
    assert_eq!(p.x, 0);
    assert_eq!(p.y, 0);

    let c = Circle::default();
    assert_eq!(c.center.x, 0);
    assert_eq!(c.center.y, 0);
    assert_eq!(c.radius, 1);

    let r = Rectangle::default();
    assert_eq!(r.top_left.x, -1);
    assert_eq!(r.top_left.y, 1);
    assert_eq!(r.bottom_right.x, 1);
    assert_eq!(r.bottom_right.y, -1);

    let a = Area::default();
    assert_eq!(a.area, 0.0);

    println!("Default test passed.");

    // --- Test Add / Sub per Point ---
    let p1 = Point { x: 10, y: 11 };
    let p2 = Point { x: 1, y: 1 };
    let p_sum = p1 + p2;
    assert_eq!(p_sum.x, 11);
    assert_eq!(p_sum.y, 12);

    let p_diff = Point { x: 0, y: 0 } - Point { x: 20, y: 30 };
    assert_eq!(p_diff.x, -20);
    assert_eq!(p_diff.y, -30);

    println!("Add/Sub test passed.");

    // --- Test GetArea ---
    let circle = Circle { center: Point::default(), radius: 2 };
    let rect = Rectangle { top_left: Point { x: 0, y: 2 }, bottom_right: Point { x: 3, y: 0 } };
    let point = Point::default();

    assert_eq!(point.get_area().area, 0.0);
    assert!((circle.get_area().area - 12.566).abs() < 0.001); // 2^2 * pi
    assert_eq!(rect.get_area().area, 6.0);

    println!("GetArea test passed.");

    // --- Test sum_area ---
    let shapes: Vec<&dyn GetArea> = vec![&circle, &rect, &point];
    let total_area = sum_area(&shapes);
    assert!((total_area.area - (12.566 + 6.0)).abs() < 0.001);

    println!("sum_area test passed. Total area: {}", total_area);
}
struct Point{
    x: i32,
    y: i32
}
struct Circle{
    center: Point,
    radius: i32
}
struct Rectangle{
    top_left: Point,
    bottom_right: Point
}
struct Area{
    area: f32
}
impl Default for Point{
    fn default()->Point{
        Point{x:0, y:0}
    }
}
impl Default for Circle{
    fn default()->Circle{
        Circle{center: Point::default(), radius: 1}
    }
}
impl Default for Rectangle{
    fn default()->Rectangle{
        Rectangle{top_left: Point{x:-1, y:1}, bottom_right: Point{x:1, y:-1}}
    }
}
impl Default for Area{
    fn default()->Area{
        Area{area: 0.0}
    }
}
impl Add for Point{
    type Output = Point;
    fn add(self, other: Point) -> Point{
        Point{x: self.x + other.x, y: self.y + other.y}
    }
}
impl Sub for Point{
    type Output = Point;
    fn sub(self, other: Point) -> Point{
        Point{x: self.x - other.x, y: self.y - other.y}
    }
}
impl Display for Area{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "Area is {}cm^2", self.area)
    }
}
trait GetArea{
    fn get_area(&self) -> Area;
}
impl GetArea for Point{
    fn get_area(&self) -> Area{
        Area{area: 0.0}
    }
}
impl GetArea for Circle{
    fn get_area(&self) -> Area{
        Area{area: self.radius as f32 * self.radius as f32 * 3.14159265359}
    }
}
impl GetArea for Rectangle{
    fn get_area(&self) -> Area{
        Area{area: (self.bottom_right.x - self.top_left.x) as f32 * (self.top_left.y - self.bottom_right.y) as f32}
    }
}
impl Add<Area> for Area{
    type Output = Area;
    fn add(self, other: Area) -> Area{
        Area{area: self.area + other.area}
    }
}
impl Add<&dyn GetArea> for Area{
    type Output = Area;
    fn add(self, other: &dyn GetArea) -> Area{
        Area{area: self.area + other.get_area().area}
    }
}
fn sum_area(slice: &[&dyn GetArea]) -> Area {
    let mut a = Area::default();
    for &s in slice{
        a = a + s;
    }
    a
}
*/

/*
fn es_07(){
    // --- Casi di test ASCII ---
    let tests = [
        ("123456789", "123", "456789"),      // prefisso presente
        ("987654321", "123", "987654321"),   // prefisso assente
        ("123", "123", ""),                   // prefisso uguale al numero
        ("123456", "", "123456"),             // prefisso vuoto
        ("", "123", ""),                       // numero vuoto
        ("12", "12345", "12"),                // prefisso più lungo del numero
    ];

    for (number, prefix, expected) in &tests {
        let result = skip_prefix(number, prefix);
        println!("skip_prefix({}, {}) = {} [{}]", number, prefix, result, if result == *expected { "OK" } else { "FAIL" });
    }

    // --- Casi di test Unicode ---
    fn skip_prefix_unicode<'a>(telephone_number: &'a str, prefix: &str) -> &'a str {
        if telephone_number.starts_with(prefix) {
            let skip_chars = prefix.chars().count();
            let mut char_indices = telephone_number.char_indices();
            let byte_index = char_indices.nth(skip_chars - 1).map_or(0, |(i, c)| i + c.len_utf8());
            &telephone_number[byte_index..]
        } else {
            telephone_number
        }
    }

    let unicode_tests = [
        ("📞12345", "📞", "12345"),            // emoji come prefisso
        ("☎️12345", "☎️", "12345"),           // emoji composta
        ("café123", "café", "123"),           // caratteri accentati
        ("你好世界123", "你好", "世界123"),       // caratteri CJK
        ("🐍⚡️123", "🐍⚡️", "123"),           // più emoji
    ];

    for (number, prefix, expected) in &unicode_tests {
        let result = skip_prefix_unicode(number, prefix);
        println!("skip_prefix_unicode({}, {}) = {} [{}]", number, prefix, result, if result == *expected { "OK" } else { "FAIL" });
    }
}
fn skip_prefix<'a>(telephone_number: &'a str, prefix: & str) -> &'a str{
    if telephone_number.starts_with(prefix){
        &telephone_number[prefix.len()..]
    }else{
        telephone_number
    }
}
*/

/*
fn es_08(){
    let chair1 = Chair { color: "red", quantity: &0 };
    let chair2 = Chair { color: "blue", quantity: &1 };
    let chair3 = Chair { color: "green", quantity: &3 };

    let wardrobe1 = Wardrobe { color: "brown", quantity: &0 };
    let wardrobe2 = Wardrobe { color: "white", quantity: &1 };
    let wardrobe3 = Wardrobe { color: "black", quantity: &4 };

    let objects: Vec<&dyn Object> = vec![&chair1, &chair2, &chair3, &wardrobe1, &wardrobe2, &wardrobe3];

    for obj in &objects {
        println!("{}", obj.build());
        println!("{}", obj.get_quantity());
        println!(); // riga vuota per leggibilità
    }

    // Test Display
    println!("{}", chair1);
    println!("{}", chair2);
    println!("{}", chair3);

    println!("{}", wardrobe1);
    println!("{}", wardrobe2);
    println!("{}", wardrobe3);
}
struct Chair<'a>{
    color: &'a str,
    quantity: &'a usize
}
struct Wardrobe<'a>{
    color: &'a str,
    quantity: &'a usize
}
trait Object{
    fn build(&self) -> &str;
    fn get_quantity(&self) -> String;
}
impl Object for Chair<'_>{
    fn build(&self) -> &str{
        "Chair has been built"
    }
    fn get_quantity(&self) -> String{
        format!("We have {} chairs.", self.quantity)
    }
}
impl Display for Chair<'_>{
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        match self.quantity{
            0 => write!(f, "No more chairs available."),
            1 => write!(f, "There is only one {} chair.", self.color),
            2 => write!(f, "We have 2 {} chairs.", self.color),
            _ => write!(f, "We have {} {} chairs.", *self.quantity, self.color)
        }
    }
}
impl Object for Wardrobe<'_>{
    fn build(&self) -> &str{
        "Wardrobe has been built"
    }
    fn get_quantity(&self) -> String{
        format!("We have {} wardrobe.", self.quantity)
    }
}
impl Display for Wardrobe<'_>{
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        match self.quantity{
            0 => write!(f, "No more wardrobe available."),
            1 => write!(f, "There is only one {} wardrobe.", self.color),
            2 => write!(f, "We have 2 {} wardrobe.", self.color),
            _ => write!(f, "We have {} {} wardrobe.", *self.quantity, self.color)
        }
    }
}
*/
fn main(){
    //es_01();
    //es_02();
    //es_03();
    //es_04();
    //es_05();
    //es_06();
    //es_07();
    //es_08();
}