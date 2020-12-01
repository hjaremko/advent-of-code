use crate::utils::Day;
use aoc_fetch::AocInput;

pub struct Day1 {
    values: Vec<i32>,
}

impl Day1 {}

impl Day for Day1 {
    fn new(input: AocInput) -> Self {
        Day1 {
            values: input.split()
        }
    }

    fn get_first_solution(&self) -> String {
        self.values
            .iter()
            .sum::<i32>()
            .to_string()
    }

    fn get_second_solution(&self) -> String {
        self.values
            .iter()
            .sum::<i32>()
            .to_string()
    }
}

#[cfg(test)]
mod part_one {
    use super::*;

    #[test]
    fn _xx() {
        // let day = Day1::new("xx".to_string());
        // assert_eq!(day.get_first_solution(), "x");
    }
}

#[cfg(test)]
mod part_two {
    use super::*;

    #[test]
    fn _xx() {
        // let day = Day1::new("xx".to_string());
        // assert_eq!(day.get_second_solution(), "x");
    }

}
