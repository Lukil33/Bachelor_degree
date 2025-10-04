use std::collections::HashMap;
use std::fs::copy;
use std::iter::from_fn;
use std::path::Iter;

enum palle{
    pelose(i32),
    gialle(String)
}

fn create_vec(bound: &i32) ->Vec<i32>{
    let mut vec = Vec::new();
    for i in 0..(*bound)+1 {
        vec.push(i);
    }
    vec
}
fn modify_odd(slice_of_integer: &mut[i32]){
    // 1 - Write a function called modify_odd that takes a mutable reference to an array slice of
    // integers slice and sets all odd numbers to 0.
    // Then write a second function that create a Vec, filled with all numbers from 0 to 100,
    // and pass it to modify_odd;
    for num in slice_of_integer{
        *num -= *num*(*num%2);
    }
}

fn count_character(string: String) -> HashMap<String,u32>{
    // 2 - Write a function count_character that takes a string consisting of ASCII characters
    // string as input and returns a HashMap. The keys of the HashMap should be the
    // characters in the string, and the values should be an u32 representing how many times
    // each character appears in the string.
    let mut map = HashMap::new();
    for char in string.chars(){
        match map.get(&String::from(char)){
            Some(x) => map.insert(String::from(char), (*x + 1)),
            None => map.insert(String::from(char), 1)
        };
    }
    map
}

fn split_rec(slice: &[i32], value: i32, pos: usize) -> Option<usize>{
    if pos >= slice.len() {
        None
    } else if slice[pos] == value{
        Some(pos)
    }else{
        split_rec(slice,value,pos+1)
    }
}
fn split_at_value(slice: &[i32], value: i32) -> Option<(&[i32],&[i32])>{
    // 3 - Write a function named split_at_value that takes two arguments: a slice of i32 called
    // slice and a single i32 value called value . The function should find the first element
    // equal to value inside slice . It should then split the slice at the corresponding index
    // and return the two resulting slices wrapped in an Option.
    // If value is not found in slice , the function should return None.
    let res = split_rec(slice,value,0)?;
    Some((&slice[0..res],&slice[res..slice.len()]))
}

fn is_contained(x: &Vec<i32>, y: &Vec<i32>) -> Option<(i32,i32)>{
    for pos_x in 0..x.len(){
        if x[pos_x] == y[0]{
            let mut check = true;
            for pos_y in 0..y.len() {
                if x[pos_x+pos_y] != y[pos_y] {
                    check = false;
                }
            }
            if check {
                return Some((pos_x as i32,(pos_x+y.len()) as i32))
            }
        }
    }
    None
}
fn sub_slice(x: &Vec<i32>, y: &Vec<i32>){
    // 4 - Write a function sub_slice that takes two &Vec<i32> as input. If the second vector is
    // contained inside the first one it prints the corresponding slice, otherwise it print Not
    // found
    match is_contained(x,y) {
        Some(x) => println!("4. Il secondo array si trova dalla posizione {} alla posizione {}",x.0,x.1),
        None => println!("4. Il secondo array non si trova all'interno del primo")
    }
}

fn max(vec: &Vec<i32>) -> Option<i32>{
    // Write a function max that takes a Vec of i32 and returns the maximum value inside
    // it.
    if vec.is_empty() {
        None
    }else if vec.len() == 1{
       Some(*(vec.get(0).unwrap()))
    }else{
        Some(std::cmp::max(*(vec.get(0).unwrap()),max(&(vec[1..].to_vec())).unwrap()))
    }
}
fn is_sorted(vec: &Vec<i32>) -> bool{
    // Write a function is_sorted that takes a Vec of i32 and returns a boolean indicating
    // whether the vector is sorted in non-decreasing order.
    if vec.is_empty() || vec.len() == 1 {
        true
    }else{
        (*(vec.get(0).unwrap()) <= *(vec.get(1).unwrap())) && is_sorted(&(vec[1..].to_vec()))
    }
}
fn insert_if_longer(vett: &mut Vec<String>,str: &String) -> bool{
    // Write a function insert_if_longer that takes a Vec of String ( vec ) and a String
    // ( string ). This function should insert string into vec only if the length of string
    // is greater than 10.
    let check = str.len() >= 10;
    if check {
        vett.push(str.clone());
    }
    check
}

/*fn build_vector(iter: Iter<i32>) -> Vec<&i32>{
    // 6 - Write a function build_vector that takes a Iter<i32> and returns the Vec<&i32>
    // containing all the elements of the iterator;
    let mut vett = Vec::new();
    for i in iter{
        vett.push(i);
    }
    vett
}*/

fn find_active_part(vec: &[i32],num: &i32) -> i32 {
    if vec.is_empty() {
        0
    }else{
        let mut res = 0;
        if vec.len() != 1 {
            res = find_active_part(&vec[1..],&std::cmp::max(*num,vec[0]));
        }
        if res > 0 {
            res += 1;
            res
        }else if *num > vec[0]{
            1
        }else{
            0
        }
    }
}
fn pancake_sort(vec: &mut Vec<i32>){
    // 7 - Write a function pancake_sort that takes a &mut Vec<i32> and sorts it using the
    // pancake sort algorithm;
    let mut active_part = find_active_part(vec,vec.get(0).unwrap());
    while active_part != 0 {
        let mut max_pos = 0;
        let mut max = vec[0];
        for num in 0..active_part {
            if vec[num as usize] > max{
                max = vec[num as usize];
                max_pos = num;
            }
        }
        let switch_max = &mut vec[0..((max_pos+1) as usize)];
        switch_max.reverse();
        let switch_active = &mut vec[0..(active_part as usize)];
        switch_active.reverse();
        active_part = find_active_part(vec,vec.get(0).unwrap());
    }
}

fn merge(fvec: &[i32],svec: &[i32]) -> Vec<i32>{
    // 8 - Write a function merge that takes two &[i32] and returns a Vec<i32> . The returned
    // vector should contain the elements of the two passed elements sorted, you can assume
    // that the passed slices are sorted;
    if fvec.is_empty() {
        Vec::from(svec)
    }else if svec.is_empty() {
        Vec::from(fvec)
    }else{
        let mut vec = Vec::new();
        if fvec[0] < svec[0] {
            vec.push(fvec[0]);
            vec = [vec,merge(&fvec[1..],svec)].concat();
        }else {
            vec.push(svec[0]);
            vec = [vec,merge(fvec,&svec[1..])].concat();
        }
        vec
    }
}


fn main() {
    // 1 - Write a function called modify_odd that takes a mutable reference to an array slice of
    // integers slice and sets all odd numbers to 0.
    // Then write a second function that create a Vec, filled with all numbers from 0 to 100,
    // and pass it to modify_odd;
    let mut vc = create_vec(&10);
    modify_odd(&mut vc);
    println!("1. {:?}",vc);

    // 2 - Write a function count_character that takes a string consisting of ASCII characters
    // string as input and returns a HashMap. The keys of the HashMap should be the
    // characters in the string, and the values should be an u32 representing how many times
    // each character appears in the string.
    let mappa = count_character(String::from("Esci dalla mia testa"));
    println!("2. {:?}",mappa);

    // 3 - Write a function named split_at_value that takes two arguments: a slice of i32 called
    // slice and a single i32 value called value . The function should find the first element
    // equal to value inside slice . It should then split the slice at the corresponding index
    // and return the two resulting slices wrapped in an Option.
    // If value is not found in slice , the function should return None.
    match split_at_value(&[2,3,5,2,5,1],1){
        Some(a) => println!("3. Slice 1: {:?} - Slice 2: {:?}",a.0,a.1),
        None => println!("3. il numero selezionato non è presente")
    }

    // 4 - Write a function sub_slice that takes two &Vec<i32> as input. If the second vector is
    // contained inside the first one it prints the corresponding slice, otherwise it print Not
    // found
    sub_slice(&create_vec(&100),&create_vec(&10));

    // 5 - Write the following functions, for each of the functions think carefully about what is the
    // best way to pass the arguments (&, &mut or passing ownership):
    // Write a function max that takes a Vec of i32 and returns the maximum value inside
    // it.
    // Write a function swap that swaps the first and last element of a vector of i32.
    // Write a function is_sorted that takes a Vec of i32 and returns a boolean indicating
    // whether the vector is sorted in non-decreasing order.
    // Write a function insert_if_longer that takes a Vec of String ( vec ) and a String
    // ( string ). This function should insert string into vec only if the length of string
    // is greater than 10.
    // Also, when possible, implement these functions recursively, not iteratively.
    let mut vettore = Vec::from([9,2,4,6,3,1,8,5,7]);
    let mut vett_str = Vec::from([String::from("gayenricofaaaaa"),String::from("supersticalifragilistichestiralitoso")]);
    let stringa = String::from("pallepelosesemprebavose");
    match max(&vettore){
        Some(x) => println!("5-1. Il massimo del vettore è: {}",x),
        None => println!("5-1. Il vettore è vuoto")
    }
    println!("5-2. Il vettore è ordinato?: {}", is_sorted(&vettore));
    println!("5-3. La stringa {} è stata inserita?: {}",stringa,insert_if_longer(&mut vett_str,&stringa));

    // 6 - Write a function build_vector that takes a Iter<i32> and returns the Vec<&i32>
    // containing all the elements of the iterator;

    // 7 - Write a function pancake_sort that takes a &mut Vec<i32> and sorts it using the
    // pancake sort algorithm;
    pancake_sort(&mut vettore);
    println!("7. {:?}",vettore);

    // 8 - Write a function merge that takes two &[i32] and returns a Vec<i32> . The returned
    // vector should contain the elements of the two passed elements sorted, you can assume
    // that the passed slices are sorted;
    let sort = merge(&[1,3,4,7,10],&[2,5,6,8,9]);
    println!("8. {:?}",sort);

    // 9 - Create a Vec that can contain both an i32 and a String
    let mut Pisnelo: Vec<palle> = Vec::new();
    Pisnelo.push(palle::gialle(String::from("Mi sento una tloiaaaa")));
    Pisnelo.push(palle::pelose(69));
    print!("9. ");
    for i in Pisnelo{
        match i {
            palle::gialle(x) => print!("{x} "),
            palle::pelose(y) => print!("{y} ")
        }
    }
    println!();

    // 10 -
}