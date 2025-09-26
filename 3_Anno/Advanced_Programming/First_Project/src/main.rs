fn main() {
    // ITERAZIONE IN GENERALE
    // Rust permette di iterare tramite funzioni native solo per alcuni tipi, non per tutti
    // La seguente lina di codice per esempio è sbagliata:
    // for n in 1.1..3.1 {
    for n in 1..5{
        println!("{}", n);
    }
    println!("\n");

    // ITERAZIONE SU ARRAY
    // into_iter svuota l'arrey nel caso in cui questo sia compsti di oggetti invece che di tipi base
    // nel caso di sotto infatti ciò comporta il mancato funzionamento del secondo for
    // let a = [String::from("palle"),String::from("gialle"),String::from("pelose")];
    let a = [1,2,3,4,5];
    for mut element in a.into_iter(){
        element += 1;
        println!("{}", element);
    }
    for element in a.iter(){
        println!("{}", element);
    }
    println!("\n");

    // non si può leggere da qualcosa che non è stato già inizializzato a qualcos'altro
    let a : i32 = 0;
    //println!("{a}");

    // Lavorare sui vettori è una fottutissima merda, poichè non puoi fare borrow di tipo diverso
    // capita spesso di non poter chiamare una funzione in quanto hai già almeno un mutable borrow attivo
    // Se decommento la linea di codice infatti parte un'errore in quanto per array ho già un mutable borrow attivo
    let mut array : [String;3] = [String::from("hello"),String::from("world"),String::from("123")];
    let (palle, sudate) = array.split_at_mut(1);
    //println!("{}",array[2]);
    println!("{}",palle[0]);
}

// La seguente funzione non può funzionare in quanto se decommentassimo il seguente valore di ritorno
// La funzione ritornerebbe un puntatore ad una zona di memoria nella quale non è più presente niente
fn dangle(palle:& String) ->& String{
    let pisnelo = String::from("pirsnelo");
    //&pisnelo
    palle
}