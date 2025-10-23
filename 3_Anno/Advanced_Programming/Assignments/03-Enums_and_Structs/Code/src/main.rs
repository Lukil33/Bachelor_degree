use std::cmp::Ordering;
use std::collections::HashMap;
use crate::Macchina::{ChickHicks, DocHudson, FrancescoBernoulli, SaettaMcQueen};

fn is_it_luhn(input: &String) -> bool {
    // 1 - Given a number determine whether it is valid per the Luhn formula, creating the function is_it_luhn
    // The Luhn algorithm is a simple checksum formula used to validate a variety of identification numbers, such as credit card numbers. Check
    // if a given string is valid Strings of length 1 or less are not valid. Spaces are allowed in the input,
    // but they should be stripped before checking. All other non-digit characters are disallowed.
    let mut res = 0;
    let mut is_pari = true;
    let mut first:Vec<i32> = Vec::new();
    let mut second:Vec<i32> = Vec::new();
    for element in input.chars(){
        if element != ' '{
            if is_pari {
                first.push(element.to_digit(10).unwrap() as i32);
            }else{
                second.push(element.to_digit(10).unwrap() as i32);
            }
            is_pari = !is_pari;
        }
    }
    if is_pari {
        res += second.iter().sum::<i32>();
        for elem in first {
            match elem {
                0..5 => res += elem*2,
                5..10 => res += (elem*2)-9,
                _ => println!("non dovrebbe poter succedere")
            }
        }
        res%10 == 0
    }else{
        res += first.iter().sum::<i32>();
        for elem in second {
            match elem {
                0..5 => res += elem*2,
                5..10 => res += (elem*2)-9,
                _ => println!("non dovrebbe poter succedere")
            }
        }
        res%10 == 0
    }
}

/*
enum fuel{
    Diesel,
    Gasoline,
    LPG,
    Methane,
    Electric
}
enum IP_version{
    V4([(i32,i32,i32); 3]),
    V6([(u32,u32,u32,u32); 8]),
}
struct point{
    length: f64,
    height: f64,
    width: f64
}
*/

enum Macchina{
    SaettaMcQueen,
    ChickHicks,
    FrancescoBernoulli,
    DocHudson
}
struct Car{
    owner_name:String,
    owner_surname:String,
    plate: String,
    model: Macchina,
}
fn recognise_owner(database: &Vec<Car>, plate: &String) -> Option<(String,String)>{
    // 3 - In Trento there is an automated car park with a camera that recognises the number plate of the car. Your task is to associate the number
    // plate with the owner of the car in order to track the price for each car owner. Create a main with an appropriate data structure already
    // initialised with some data. Create a function recognise_owner that, given the data structures mentioned above and the number of car
    // plate, returns an Optional value of the owner of the car
    for elem in database.iter(){
        if elem.plate.cmp(plate) == Ordering::Equal{
            match elem.model {
                Macchina::SaettaMcQueen => println!("Sei un figo"),
                _ => println!("Non sei saetta, non sei nessuno")
            }
            return Some((elem.owner_name.clone(),elem.owner_surname.clone()));
        }
    }
    None
}

/*
#[derive(Eq, Hash, PartialEq)]
enum Item {
    Chesterfield,
    Marlboro,
    Benson,
    LuckyStrike
}
enum Coin {
    Cents1,
    Cents2,
    Cents5,
    Cents10,
    Cents20,
    Cents50,
    Euro1,
    Euro2,
    Euro5
}
impl Coin {
    fn to_cents(self: Coin) -> Option<u32> {
        match self {
            Coin::Cents10 => Some(10),
            Coin::Cents20 => Some(20),
            Coin::Cents50 => Some(50),
            Coin::Euro1 => Some(100),
            Coin::Euro2 => Some(200),
            Coin::Euro5 => Some(500),
            _=>None
        }
    }
}
struct VendingMachine {
    coins: u32,
    items: HashMap<Item, usize>
}
impl VendingMachine {
    fn new(map: HashMap<Item,usize>) -> VendingMachine {
        VendingMachine{
            coins: 0,
            items: map
        }
    }
    fn add_item(&mut self, item: Item, val:usize) {
        let mut check = false;
        for elem in self.items.iter_mut(){
            if *elem.0 == item {
                *elem.1 += val;
                check = true;
            }
        }
        if !check {
            self.items.insert(item,val);
        }
    }
    fn insert_coin(&mut self, coin: Coin) -> Result<&str,&str> {
        match coin.to_cents() {
            Some(cents) => {self.coins += cents; Result::Ok("Tutto a posto")},
            None => Result::Err("Le monete inserite non sono valide")
        }
    }
    fn get_item_price(item: &Item) -> u32 {
        match item {
            Item::Benson => 500,
            Item::Chesterfield => 550,
            Item::Marlboro => 600,
            Item::LuckyStrike => 450
        }
    }
    fn buy(&self, item: Item) -> Result<u32,&str> {
        if Self::get_item_price(&item) > self.coins {
            Result::Err("Credito insufficiente")
        }else{
            Result::Ok(self.coins - Self::get_item_price(&item))
        }
    }
}
*/

#[derive(Debug)]
struct Date {
    date: u8,
    month: u8,
    year: u16
}
impl std::fmt::Display for Date {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f,"{}/{}/{}",self.date,self.month,self.year)
    }
}
#[derive(Debug)]
struct Hour {
    hour: u8,
    minutes: u8
}
impl std::fmt::Display for Hour {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f,"{}:{}",self.hour,self.minutes)
    }
}
#[derive(Debug)]
struct BoxShipping {
    name: String,
    barcode: String,
    shipment_date: Date,
    shipment_hour: Hour
}
impl std::fmt::Display for BoxShipping {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f,"Name: {}\nReconsignment code: {}\nDate & Time: {} {}",self.name,self.barcode,self.shipment_date,self.shipment_hour)
    }
}

fn main() {
    // 1 - Given a number determine whether it is valid per the Luhn formula, creating the function is_it_luhn
    // The Luhn algorithm is a simple checksum formula used to validate a variety of identification numbers, such as credit card numbers. Check
    // if a given string is valid Strings of length 1 or less are not valid. Spaces are allowed in the input,
    // but they should be stripped before checking. All other non-digit characters are disallowed.
    // Ex 1: valid card number
    // 4539 3195 0343 6467
    // The first step is to double every second digit, starting from the right. We will be doubling
    // 43 39 04 66
    // If doubling the number results in a number greater than 9 then subtract 9 from the product. The results of our doubling:
    // 8569 6195 0383 3437
    // Then sum all the digits is 80. If the sum is divisible by 10, then the number is valid.
    println!("1. La stringa è luhn?: {}", is_it_luhn(&String::from("4539 3195 0243 6467")));

    // 2 - For the following examples, decide which of the composite data structures is better (enum or structs). Then implement them
    // you are Rick, a car shop owner, and you have to choose the fuel of your car between Diesel, Gasoline, LPG, Methane and Electric
    // you have to program the recognition of the IP version of a router. Remember that IPv4 is formatted with 4 group of 3 integer values
    // (from 0 to 255), IPv6 is instead formatted with 8 groups of 4 hexadecimal (so no strings!) values.
    // you have to track points in a 3-dimensional space, with the f64 values for each dimension

    // 3 - In Trento there is an automated car park with a camera that recognises the number plate of the car. Your task is to associate the number
    // plate with the owner of the car in order to track the price for each car owner. Create a main with an appropriate data structure already
    // initialised with some data. Create a function recognise_owner that, given the data structures mentioned above and the number of car
    // plate, returns an Optional value of the owner of the car
    let mut database:Vec<Car> = Vec::new();
    database.push(Car{
        owner_name: String::from("Luca"),
        owner_surname: String::from("Prigione"),
        plate: String::from("PalleRosse"),
        model: SaettaMcQueen
    });
    database.push(Car{
        owner_name: String::from("Enrico"),
        owner_surname: String::from("Faa"),
        plate: String::from("PalleVerdi"),
        model: ChickHicks
    });
    database.push(Car{
        owner_name: String::from("Raffaele"),
        owner_surname: String::from("Modroni"),
        plate: String::from("PalleItaliane"),
        model: FrancescoBernoulli
    });
    database.push(Car{
        owner_name: String::from("Goran"),
        owner_surname: String::from("Devetak"),
        plate: String::from("PalleVecchie"),
        model: DocHudson
    });
    match recognise_owner(&database,&String::from("PalleVerdi")){
        Some((nome,cognome)) => println!("3. La macchina apartiene a: {} {}",nome,cognome),
        None => println!("3. La macchina non sembra apartenere a nessuno, il malvivente è ancora in giro"),
    }

    // 4 - Create a vending machine.
    // 1. Define an enum Item that lists the available items inside the machine (e.g. Coke, Coffee, ecc).
    // 2. Define the enum Coin that contains the coin type accepted by the machine (e.g. Coin::FiftyCents , Coin::Euro2 ). And
    // implement the method to_cents that convert a Coin variant into a u32 representing the number of cents (e.g. 1€ => 100 , 20¢ =>
    // 20 ).
    // 3. Define the struct VendingMachine that has the following fields:
    // coins: u32
    // This field represents the number of cents currently held inside the machine (e.g. if the user inserted 1€ and 10¢, then the coins
    // should be at 110 ).
    // items: HashMap<Item, usize>
    // This field should associate an Item type to the number of available items to buy.
    // Now implement the following methods for VendingMachine:
    // new method that takes an HashMap of Items contained in the VendingMachine initially and returns a new instance of the
    // struct , set coins to 0.
    // add_item takes an Item variant and a usize ; increments the number of the specified type of items contained by the machine
    // insert_coin takes a Coin variant and increment the field coins by the right value. Returns a Result<&str, &str> with the
    // confirmation/error message.
    // get_item_price takes an &Item variant and returns a u32 item price.
    // buy takes a Item variant and returns a Result<u32, &str> if you have enough money it returns the change, if you don't, it
    // returns the error as a &str .
    // Note:
    // For using Item as an HashMap key it needs to implement PartialEq , Eq and Hash . Keep in mind that you can derive them.

    // 5 - Implement two tuple structs named Date and Hour . The former takes u8 , u8 and u16 and the latter two u8
    // Implement a BoxShipping struct, with the fields name: String , barcode: String , shipment_date: Date and shipment_hour: Hour`
    // Make BoxShipping displayable both with {:?} as well as with {} argument in the println! macro.
    // Note:
    // *Date and Hour structs should be formatted correctly, ex. 12/01/2001 and 09:00
    let orario = Hour { hour: 02, minutes: 38};
    let giorno = Date {date: 01, month: 12, year: 2004};
    let pacco = BoxShipping{name: String::from("Luca Prigione"), barcode: String::from("R moscia"), shipment_date: giorno, shipment_hour: orario};
    println!("{}",pacco);

    // 6 -  How was that book called? Programming crust? Nevermind.
    // Create BUP's library system. It should be able to store books, articles and magazines.
    // Each book, article and magazine should have a name, a code and a year of publication.
    // Books should also have an author and a publishing company.
    // Articles should have an orchid.
    // Magazines should have a number and a month.
    // Then implement the methods to add a book, an article and a magazine to the library system.
    // Finally, implement a method to print the library system via the {} argument in the println! macro.
    // TODO()
}