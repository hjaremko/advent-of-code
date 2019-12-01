//2018
use crate::utils::Day;
use std::collections::HashSet;

pub struct Day1 {
    values: Vec<i32>,
}

impl Day for Day1 {
    fn new(input: String) -> Self {
        let input: Vec<i32> = input
            .split_ascii_whitespace()
            .map(|x| x.parse().ok().unwrap())
            .collect();

        Day1 { values: input }
    }

    fn get_first_solution(&self) -> String {
        let sum: i32 = self.values.iter().sum();
        sum.to_string()
    }

    fn get_second_solution(&self) -> String {
        let mut frequency = 0;
        let mut frequencies = HashSet::new();

        for value in self.values.iter().cycle() {
            frequency += *value;

            if frequencies.contains(&frequency) {
                return frequency.to_string();
            }

            frequencies.insert(frequency);
        }

        "".to_string()
    }
}
