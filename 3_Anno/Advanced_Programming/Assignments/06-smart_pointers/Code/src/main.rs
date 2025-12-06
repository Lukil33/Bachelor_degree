/*
fn es_01(){}
struct TreeNode<T:PartialOrd + Clone>{

    value: T,
    left: Option<Box<TreeNode<T>>>,
    right: Option<Box<TreeNode<T>>>
}
impl<T:PartialOrd + Clone> TreeNode<T>{
    fn new(value: T) -> TreeNode<T>{
        TreeNode{value, left: None, right: None}
    }
    fn from_vec(vec: &Vec<T>) -> Option<TreeNode<T>>{
        let mut iter = vec.iter();
        let first = iter.next()?.clone();   // Nessun panic
        let mut tree = TreeNode::new(first);
        for v in iter {
            tree.insert(v.clone());
        }
        Some(tree)
    }
    fn insert(&mut self, value: T){
        if value < self.value {
            match self.left {
                Some(ref mut left) => left.insert(value),
                None => self.left = Some(Box::new(TreeNode::new(value))),
            }
        } else {
            match self.right {
                Some(ref mut right) => right.insert(value),
                None => self.right = Some(Box::new(TreeNode::new(value))),
            }
        }
    }
}
*/

/*
use std::cell::RefCell;
use std::ops::Deref;
use std::rc::Rc;

fn es_02(){}
#[derive(Debug)]
struct Car{
    model: String,
    year: u32,
    price: u32,
    rent: bool
}
impl Car{
    fn new(model: String, year: u32, price: u32, rent: bool) -> Car{
        Car{model, year, price, rent}
    }
}
impl Default for Car{
    fn default() -> Self {
        Car{model: String::from("Fiat"), year: 2004, price: 6969, rent:false}
    }
}
struct CarDealer{
    v: Vec<Rc<RefCell<Car>>>
}
impl CarDealer{
    fn new() -> CarDealer{
        CarDealer{v:Vec::new()}
    }
    fn add_car(&mut self, car: Car){
        self.v.push(Rc::new(RefCell::new(car)));
    }
    fn print_car(&self){
        self.v.iter().for_each(|c| println!("{:?}", c))
    }
    fn rent_user(&mut self, user: &mut User, model: String){
        let pos = self.v.iter().position(|c| c.borrow_mut().model == model);
        match pos {
            Some(i) => {
                self.v.get(i).unwrap().borrow_mut().rent = true;
                user.car = Some(self.v.get(i).unwrap().clone())
            },
            None => println!("Car not found")
        }
    }
    fn end_rental(user: &mut User){
        match user.car{
            Some(ref T) => {
                T.borrow_mut().rent = false;
                user.car = None;
            },
            None => println!("User has no car")
        }
    }
}
struct User{
    car: Option<Rc<RefCell<Car>>>
}
impl User{
    fn print_car(&self){
        match self.car{
            Some(ref T) => println!("{:?}", T),
            None => println!("User has no car")
        }
    }
}
*/

/*
use std::cell::RefCell;
use std::ops::Deref;
use std::rc::Rc;
use std::task::Context;

fn es_03(){}
trait Sound{
    fn make_sound(&self) -> String;
}
struct Animal{
    name: String,
    sound: String
}
impl Sound for Animal{
    fn make_sound(&self) -> String{
        format!("{} makes this sound: {} ", self.name, self.sound)
    }
}
struct FarmCell{
    element: Box<dyn Sound>,
    next: Option<Box<FarmCell>>
}
impl FarmCell{
    fn new(element: Box<dyn Sound>) -> FarmCell{
        FarmCell{element, next: None}
    }
    fn insert(&mut self, next: FarmCell){
        match self.next.as_mut(){
            Some(f) => f.insert(next),
            None => self.next = Some(Box::new(next))
        }
    }
}
impl Sound for FarmCell{
    fn make_sound(&self) -> String{
        let mut sound = self.element.make_sound();
        match self.next.as_ref(){
            Some(f) => {sound += &f.make_sound(); sound},
            None => sound
        }
    }
}
*/

/*
fn es_04(){}
struct PublicStreetlight{
    id: usize,
    on: bool,
    burn_out: bool
}
impl PublicStreetlight{
    fn new(id: usize) -> PublicStreetlight{
        PublicStreetlight{id, on: false, burn_out: false}
    }
}
impl Default for PublicStreetlight{
    fn default() -> Self {
        Self::new(0)
    }
}
struct PublicIllumination{
    lights: Vec<PublicStreetlight>
}
impl PublicIllumination{
    fn new(vec: Vec<PublicStreetlight>) -> Self{
        PublicIllumination{lights: vec}
    }
}
impl Default for PublicIllumination{
    fn default() -> Self {
        PublicIllumination{lights: vec![PublicStreetlight::default()]}
    }
}
impl Iterator for PublicIllumination{
    type Item = PublicStreetlight;
    fn next(&mut self) -> Option<Self::Item>{
        for (i,y) in self.lights.iter().enumerate(){
            if y.burn_out {
                return Some(self.lights.remove(i));
            }
        }
        None
    }
}
*/

/**/
fn es_05(){}
use std::marker::PhantomData;
trait CompileTimeNode{
    type LeftType;
    type RightType;
    fn is_none() -> bool;
}
struct NullNode{}
struct Node<L,R>{
    left: PhantomData<L>,
    right: PhantomData<R>
}
fn count_nodes<T>() -> usize{
    
}


fn main() {
    //es_01();
    //es_02();
    //es_03();
    //es_04();
    es_05();
}
