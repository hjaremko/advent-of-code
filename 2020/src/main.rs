use crate::utils::{get_day_year, Day, init};
use std::time::SystemTime;
use aoc_fetch::load_or_fetch_input;
use log::{error, LevelFilter};

pub mod days;

#[macro_use]
pub mod utils;

#[macro_use]
extern crate clap;

fn main() {
    init(LevelFilter::max()).unwrap();

    let (day, year) = get_day_year();
    let input = load_or_fetch_input(&day, &year);

    if let Err(e) = input {
        error!("{}", e);
        return;
    }

    let input = input.unwrap();

    match day.as_ref() {
        "1" => {
            solve!(1, input);
        }
        _ => {
            println!("Day {}-{} not yet supported", day, year);
        }
    };
}
