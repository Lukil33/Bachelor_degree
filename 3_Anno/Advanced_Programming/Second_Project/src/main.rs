use std::cell::RefCell;
use std::fmt::{Display, Formatter};
use std::rc::Rc;

struct Node<T>{
    elem: T,
    next: Option<Rc<RefCell<Node<T>>>>,
    prev: Option<Rc<RefCell<Node<T>>>>
}
struct List<T>{
    field: usize,
    head: Option<Rc<RefCell<Node<T>>>>,
    tail: Option<Rc<RefCell<Node<T>>>>
}
impl<T:PartialEq> PartialEq for Node<T>{
    fn eq(&self, other: &Self) -> bool {
        self.elem == other.elem
    }
}
impl<T: Display> Display for Node<T>{
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.elem)
    }
}
impl<T: PartialEq> PartialEq for List<T>{
    fn eq(&self, other: &Self) -> bool{
        if self.field != other.field { return false; };
        let mut curr_self = self.head.clone();
        let mut curr_other = other.head.clone();
        while let (Some(x),Some(y)) = (curr_self, curr_other){
            if x != y { return false; }
            curr_self = x.borrow().next.clone();
            curr_other = y.borrow().next.clone();
        }
        true
    }
}
impl<T: Display> Display for List<T>{
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        let mut curr = self.head.clone();
        while let Some(x) = curr{
            write!(f, "{}", x.borrow().elem)?;
            curr = x.borrow().next.clone();
        }
        Ok(())
    }
}
impl<T> List<T> where T: PartialEq + Display{
    fn new() -> Self{
        List{field: 0, head: None, tail: None}
    }
    fn print_list(&self){
        let mut curr = self.head.clone();
        while let Some(x) = curr{
            println!( "{}", x.borrow().elem);
            curr = x.borrow().next.clone();
        }
    }
    fn push(&mut self, elem: T){
        let node = Rc::new(RefCell::new(Node{elem, next: None, prev: None}));
        match self.head{
            Some(ref x) => {x.borrow_mut().prev = Some(node.clone()); node.borrow_mut().next = Some(x.clone());},
            None => {self.tail = Some(node.clone());}
        }
        self.head = Some(node.clone());
        self.field += 1;
    }
    fn pop(&mut self) -> Option<T>{
        self.head.take().map(|old_head| {
            if let Some(next) = old_head.borrow_mut().next.take() {
                next.borrow_mut().prev = None;
                self.head = Some(next);
            } else {
                self.tail = None;
            }

            self.field -= 1;
            Rc::try_unwrap(old_head).ok().unwrap().into_inner().elem
        })
    }
    
}

fn main() {
    let mut list: List<i32> = List::new();
    list.push(1);
    list.push(2);
    list.push(3);
    list.print_list();
}
