use crate::utils::{get_day_year, get_input, Day};
use std::time::SystemTime;

pub mod days;

#[macro_use]
pub mod utils;

#[macro_use]
extern crate clap;

fn main() {
    let (day, year) = get_day_year();
    let input = get_input(&day, &year);

    match day.as_ref() {
        "1" => {
            solve!(1, input);
        }
        _ => {
            println!("Day {}-{} not yet supported", day, year);
        }
    };
}
