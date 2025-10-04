use std::collections::HashMap;
use std::ops::Add;
use std::ptr::hash;
use std::string;
const light_speed:i64 = 299792458;
fn string_reverse(input: &str) -> String {
    // 1 - Write a function string_reverse that takes a &str as input and returns it, reversed as a String
    let stringa_reversata = input.chars().rev();
    let mut risposta = String::new();
    for i in stringa_reversata.into_iter(){
        risposta.push(i);
    }
    risposta
}
fn bigger(f_num: i32,s_num: i32) -> i32 {
    // 2 - Write a function bigger that takes two i32 and returns the bigger number ( i32 ) without using
    // another function call and additional variables;
    if (f_num - s_num > 0) {
        f_num
    } else {
        s_num
    }
}
fn multiply(f_num: i32,s_num: f32,t_num: f64) -> f64 {
    // 3 - Write a function multiply that takes an i32 , a f32 and a f64 and returns the multiplication of the
    // three of them as a f64 value;
    f64::from(f_num)*f64::from(s_num)*t_num
}
fn e_equals_mc_squared(mass: f32) -> f64 {
    // 4 - Write a function e_equals_mc_squared that takes as input a f32 representing the mass, and that
    // uses a globally-defined constant containing the value of the speed of light in a vacuum (expressed in
    // m/s). The function outputs the energy equivalent to the mass input;
    (mass as f64)*(light_speed.pow(2) as f64)
}
fn max_min(vec: &Vec<i32>) -> Option<(i32,i32)> {
    // 5 - Given a vector of i32 , create a function max_min that returns the maximum and the minimum value
    // inside that vector;
    if vec.len() == 0 {
        None
    }else{
        let mut min = vec[0];
        let mut max = vec[0];
        for elem in vec.iter(){
            if *elem < min {
                min = *elem;
            }else if *elem > max {
                max = *elem;
            }
        }
        Some((min,max))
    }
}
fn lord_farquaad(parola: &String) -> String {
    // 6 - Write a function lord_farquaad that takes a String and outputs another String in which
    // every character 'e' is substituted by the character '💥';
    let stringa = parola.as_str();
    let mut res = String::new();
    for character in stringa.chars(){
        if character == 'e' {
            res.push('💥');
        }else{
            res.push(character);
        }
    }
    res
}
fn function(map: HashMap<String,f32>,furniture: String) -> f32 {
    // 7 - In the main function initialize a HashMap<String, f32> called furniture that stores the pair
    // String as key and f32 as value, where the String is the name of the furniture and the f32 is its
    // price. Then write a function that borrows the HashMap , takes a furniture: String as input and
    // returns the corresponding f32 . If there is no such furniture in the HashMap , return -1.0 ;
    match map.get(&furniture){
        Some(x) => *x,
        None => -1.0
    }
}
fn append(parola: &String) -> String {
    // 8 - Write a function append that takes a String , appends the word "foobar" to it and returns it.
    // Then write a main function in which you:
    // - Declare a String initialized with some text.;
    // - Pass the String to the function append ;
    // - Print the original String and the one returned by append ;
    // (do it in this order!)
    let mut nuova_parola = parola.clone();
    nuova_parola.insert_str(nuova_parola.len(), "foobar");
    nuova_parola
}
fn len_arm_rec(num: &i32) -> i32{
    if *num == 0{
        0
    }else{
        1+len_arm_rec(&(*num/10))
    }
}
fn arm_rec(num: &i32, len:&i32) -> i32{
    if *num == 0{
        0
    }else{
        (num%10).pow(*len as u32)+arm_rec(&(*num/10),len)
    }
}
fn is_armstrong(num: &i32) -> bool {
    // 9 - An Armstrong number is a number that is the sum of its own digits each raised to the power of the
    // number of digits.
    // For example:
    // 9 is an Armstrong number, because 9 = 91 = 9
    // 10 is not an Armstrong number, because 10 ≠ 12 + 02 = 1
    // 153 is an Armstrong number, because: 153 = 13 + 53 + 33 = 1 + 125 + 27 = 153
    // 154 is not an Armstrong number, because: 154 ≠ 13 + 53 + 43 = 1 + 125 + 64 = 190
    // Write the function is_armstrong that determines whether a number is an Armstrong number;
    let len = len_arm_rec(num);
    arm_rec(num,&len) == *num
}

fn main() {
    // 1 - Write a function string_reverse that takes a &str as input and returns it, reversed as a String
    let reverse= string_reverse("Hello world");
    println!("1. {}",reverse);

    // 2 - Write a function bigger that takes two i32 and returns the bigger number ( i32 ) without using
    // another function call and additional variables;
    let bigg= bigger(3,4);
    println!("2. {}",bigg);

    // 3 - Write a function multiply that takes an i32 , a f32 and a f64 and returns the multiplication of the
    // three of them as a f64 value;
    let mult= multiply(3, 4.0, 5.0);
    println!("3. {}",mult);

    // 4 - Write a function e_equals_mc_squared that takes as input a f32 representing the mass, and that
    // uses a globally-defined constant containing the value of the speed of light in a vacuum (expressed in
    // m/s). The function outputs the energy equivalent to the mass input;
    let energy=  e_equals_mc_squared(1.0);
    println!("4. {}",energy);

    // 5 - Given a vector of i32 , create a function max_min that returns the maximum and the minimum value
    // inside that vector;
    let v = Vec::from([1,0,3,5,7,2]);
    match max_min(&v) {
        Some(a) => println!("5. Min: {}, Max: {}",a.0,a.1),
        None => println!("5. Array vuoto")
    }

    // 6 - Write a function lord_farquaad that takes a String and outputs another String in which
    // every character 'e' is substituted by the character '💥';
    let frase_esplosa= lord_farquaad(&String::from("che belle le palle gialle"));
    println!("6. {}",frase_esplosa);

    // 7 - In the main function initialize a HashMap<String, f32> called furniture that stores the pair
    // String as key and f32 as value, where the String is the name of the furniture and the f32 is its
    // price. Then write a function that borrows the HashMap , takes a furniture: String as input and
    // returns the corresponding f32 . If there is no such furniture in the HashMap , return -1.0 ;
    let scores:HashMap<String,f32> = HashMap::new();
    let res = function(scores, String::from("Pallesudate"));
    println!("7. res = {}",res);

    // 8 - Write a function append that takes a String , appends the word "foobar" to it and returns it.
    // Then write a main function in which you:
    // - Declare a String initialized with some text.;
    // - Pass the String to the function append ;
    // - Print the original String and the one returned by append ;
    // (do it in this order!)
    let prima_parola = String::from("Mi piace il ");
    let seconda_parola = append(&prima_parola);
    println!("8. Prima parola: {} - Seconda parola: {}",prima_parola,seconda_parola);

    // 9 - An Armstrong number is a number that is the sum of its own digits each raised to the power of the
    // number of digits.
    // For example:
    // 9 is an Armstrong number, because 9 = 91 = 9
    // 10 is not an Armstrong number, because 10 ≠ 12 + 02 = 1
    // 153 is an Armstrong number, because: 153 = 13 + 53 + 33 = 1 + 125 + 27 = 153
    // 154 is not an Armstrong number, because: 154 ≠ 13 + 53 + 43 = 1 + 125 + 64 = 190
    // Write the function is_armstrong that determines whether a number is an Armstrong number;
    let n = 153;
    let armstrong_number = is_armstrong(&n);
    println!("9. Il numero {} è armstrong?: {}",n,armstrong_number);
}