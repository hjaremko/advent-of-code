use clap::App;
use reqwest::header::COOKIE;
use reqwest::Client;
use std::path::Path;
use std::str::FromStr;
use std::{env, fs};

pub mod intcode;

pub trait Day {
    fn new(input: String) -> Self;
    fn get_first_solution(&self) -> String;
    fn get_second_solution(&self) -> String;
}

pub fn get_day_year() -> (String, String) {
    let yaml = load_yaml!("../cli.yml");
    let matches = App::from_yaml(yaml).get_matches();
    let day = matches.value_of("day").unwrap().to_string();
    let year = matches.value_of("year").unwrap_or("2019").to_string();

    (day, year)
}

pub fn fetch_input(day: &str, year: &str, session: &str) -> String {
    eprintln!("Fetching input for day {}-{}", day, year);

    let url = format!("https://adventofcode.com/{}/day/{}/input", year, day);
    let client = Client::new();
    let input = client
        .get(&url)
        .header(COOKIE, format!("session={}", session))
        .send()
        .unwrap()
        .text()
        .unwrap();

    if input.contains("Not Found") {
        panic!("Puzzle for day {} is not live yet", day);
    }

    if input.contains("log in") {
        panic!("Session cookie is invalid");
    }

    input
}

fn save_input(day: &str, year: &str, input_path: &str, input: &str) {
    eprintln!("Saving input for day {}-{} to {}", day, year, input_path);

    let input_dir = "input";

    if !Path::new(input_dir).exists() {
        fs::create_dir(input_dir).expect("Unable to create input directory");
    }

    fs::write(input_path, input).expect("Unable to write the file");
}

pub fn get_input(day: &str, year: &str) -> String {
    let session_cookie = env::var("AOC_SESSION").expect("Expected a token in the environment");
    let input_path = format!("input/input-{}-{}.txt", year, day);

    if Path::new(&input_path).exists() {
        eprintln!("Loading input for day {}-{} from {}", day, year, input_path);
        fs::read_to_string(input_path).expect("Unable to read the file")
    } else {
        let input = fetch_input(day, year, &session_cookie);
        save_input(day, year, &input_path, &input);
        input
    }
}

macro_rules! measure {
    ($self:ident, $f:ident) => {{
        let timer = SystemTime::now();
        let duration = SystemTime::now().duration_since(timer).unwrap();
        let result = $self.$f();
        let took = format!("{}.{:09}s", duration.as_secs(), duration.subsec_nanos());
        (result, took)
    }};
}

macro_rules! solve {
    ($day:expr, $input:expr) => {
        println!("⋆ DAY {} ⋆", $day);
        paste::expr! {
            let day = days::[<day $day>]::[<Day $day>]::new($input);
            let (answer, time) = measure!(day, get_first_solution);
            println!("PART ONE: {}, {}", time, answer);
            let (answer, time) = measure!(day, get_second_solution);
            println!("PART TWO: {}, {}", time, answer);
        }
    };
}

pub fn parse_to_vec<T: FromStr>(input: String) -> Vec<T> {
    input
        .split_ascii_whitespace()
        .map(|x| x.parse().ok().unwrap())
        .collect()
}
