use crate::utils::{get_day_year, init, Day};
use aoc_fetch::load_or_fetch_input;
use log::{error, info, warn, LevelFilter};
use std::time::SystemTime;

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

        "2" => {
            solve!(2, input);
        }

        "3" => {
            solve!(3, input);
        }

        "4" => {
            solve!(4, input);
        }

        _ => {
            warn!("Day {}-{} not yet implemented", day, year);
        }
    };
}
