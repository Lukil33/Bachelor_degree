use std::collections::HashMap;

struct Person{
    name: String, age: u8
}
enum Value{
    Int(i32), Text(String)
}
fn string_and_str(){
    // String & str

    // Converti una String in &str senza clonare. (Usa borrowing)
    let s = String::from("palle");
    let palle = &s as &str;
    println!("{:?}",palle);

    // Converti una &str in String per poterne possedere e modificare il contenuto.
    let s = "palle";
    let palle = s.to_string();
    println!("{:?}",palle);

    // Estrai il primo carattere da una String come char.
    let s = String::from("palle");
    let palle = s.chars().next().unwrap();
    println!("{:?}",palle);

    // Data una Vec<String>, crea una Vec<&str> con borrowing.
    let vec = vec![String::from("palle"),String::from("gialle"),String::from("blu")];
    let palle: Vec<&str> = vec.iter().map(|s| s.as_str()).collect();
    println!("{:?}",palle);

    // Da una Vec<&str>, crea una Vec<String> copiando i dati
    let vec = vec!["palle","gialle","blu"];
    let palle: Vec<String> = vec.iter().map(|s| s.to_string()).collect();
    println!("{:?}",palle);
}
fn option_and_result(){
    // Option & Result

    // Converti un Option<String> in una String, usando "default" come valore fallback.
    let o: Option<String> = Some(String::from("Palle"));
    let palle = o.unwrap_or("default".to_string());
    println!("{:?}",palle);

    // Converti un Result<String, String> in un Option<String>, scartando l’errore.
    let r: Result<String,String>= Ok("palle".to_string());
    let palle = r.ok();
    println!("{:?}",palle);

    // Scrivi una funzione che prende un &str e restituisce Result<i32, String>.
    // Es: "123" → Ok(123), "abc" → Err("Not a number")
    let s = "1a3";
    let palle = s.parse::<i32>().map_err(|_|"non era un numero".to_string());
    println!("{:?}",palle);

    // Data una Vec<Option<i32>>, crea una nuova Vec<i32> che contiene solo i valori Some.
    let v = vec![Some(3), Some(4), None];
    let palle: Vec<i32> = v.iter().filter_map(|e| *e).collect();
    println!("{:?}",palle);

    // Scrivi una funzione che prende una Vec<&str> e restituisce un Result<Vec<u32>, String>.
    // Fallisce se una delle stringhe non è un numero.
    let v = vec!["123","1234","0385"];
    let palle: Vec<_> = v.into_iter().map(|s| s.parse::<u32>().map_err(|_| format!("Invalid input: {}", s))).collect();
    println!("{:?}",palle);
}
fn vectors(){
    // Vectors

    // Converti un array [i32; 5] in un Vec<i32>.
    let a = [1,2,3,4,5];
    let palle = a.to_vec();
    println!("{:?}",palle);

    // Converti un Vec<i32> in una String, separando i numeri con virgole.
    // Es: [1, 2, 3] → "1,2,3"
    let v = [1,2,3,4,5].to_vec();
    let palle= v.iter().map(|e| (*e).to_string()).collect::<Vec<String>>().join(",");
    //Non so come unire tutte le stringhe presenti all'interno del vettore
    println!("{:?}",palle);

    // Scrivi una funzione che prende un Vec<String> e restituisce una HashMap<String, usize>, dove la chiave è la parola e il valore è la sua lunghezza
    let v = vec![String::from("palle"),String::from("gialle"),String::from("blu")];
    let palle: HashMap<String, usize>= v.into_iter().map(|e| (e.clone(),e.len())).collect();
    println!("{:?}",palle);

    // Da una HashMap<String, i32>, crea una Vec<String> con i soli valori in formato stringa (i32 → String).
    let h: HashMap<String, i32> = HashMap::from([("palle".to_string(),324),("pollo".to_string(),325)]);
    let palle: Vec<String> = h.into_iter().map(|e| e.1.to_string()).collect();
    println!("{:?}",palle);
}
fn struct_and_enum(){
    // Struct & Enum

    //Crea una struct Person { name: String, age: u8 } e scrivi una funzione che prende una String come "Mario,30" e restituisce Option<Person>.
    let s = "Mario,30".to_string();
    let palle = s.split_at(s.find(",").unwrap_or(0));
    println!("{:?} - {:?}",palle.0,palle.1);
    // Ho fatto la parte più importante, ovvero splittare la stringa, per la funzione... sono pigro

    // Crea un enum Value { Int(i32), Text(String) } e una funzione che prende un Value e restituisce una String rappresentativa:
    // Int(42) → "42"
    // Text("ciao") → "ciao"
    let v = Value::Int(23456);
    let palle = match v { Value::Int(x)=>x.to_string(),Value::Text(x)=>x };
    println!("{:?}",palle);

    // Da una Vec<Value> crea una Vec<String> convertendo ogni Value in stringa come sopra
    let v = vec![Value::Int(23456),Value::Text("Palle".to_string()),Value::Int(69)];
    let palle: Vec<String> = v.into_iter().map(|v| match v { Value::Int(x)=>x.to_string(),Value::Text(x)=>x }).collect();
    println!("{:?}",palle);
}
fn hashmap(){
    // HashMap

    // Data una Vec<&str>, costruisci una HashMap<&str, usize> dove la chiave è la parola e il valore la sua lunghezza.
    let v = vec!["palle","gialle","blu"];
    let palle: HashMap<&str, usize> = v.into_iter().map(|e| (e,e.len())).collect();
    println!("{:?}",palle);

    // Scrivi una funzione che prende un HashMap<String, String> e restituisce una Vec<(String, usize)>, dove il usize è la lunghezza del valore.
    let h = HashMap::from([("palle".to_string(),"palle".to_string()),("pollo".to_string(),"pollo".to_string())]);
    let palle: Vec<(String, usize)> = h.into_iter().map(|e| (e.1.clone(),e.1.len())).collect();
    println!("{:?}",palle);

    // Data una HashMap<String, i32>, crea un nuovo HashMap<String, String> con i numeri convertiti in testo.
    let h = HashMap::from([("palle".to_string(),123),("pollo".to_string(),456)]);
    let palle: HashMap<String, String> = h.into_iter().map(|e| (e.0,e.1.to_string())).collect();
    println!("{:?}",palle);
}

pub fn main(){
    // CONVERSIONI
    // string_and_str();
    // option_and_result();
    // vectors();
    // struct_and_enum();
    // hashmap()
}