use crate::utils::{parse_to_vec, Day};

pub struct Day1 {
    values: Vec<i32>,
}

impl Day1 {
    pub fn reduce(fuel: &i32) -> i32 {
        (fuel / 3) - 2
    }

    pub fn fuel_down(fuel: &i32) -> i32 {
        let mut fuel = Day1::reduce(&fuel);
        let mut used = 0;

        while fuel > 0 {
            used += fuel;
            fuel = Day1::reduce(&fuel);
        }

        used
    }
}

impl Day for Day1 {
    fn new(input: String) -> Self {
        Day1 {
            values: parse_to_vec::<i32>(input),
        }
    }

    fn get_first_solution(&self) -> String {
        self.values
            .iter()
            .map(Day1::reduce)
            .sum::<i32>()
            .to_string()
    }

    fn get_second_solution(&self) -> String {
        self.values
            .iter()
            .map(Day1::fuel_down)
            .sum::<i32>()
            .to_string()
    }
}

#[cfg(test)]
mod part_one {
    use super::*;

    #[test]
    fn _12() {
        let day = Day1::new("12".to_string());
        assert_eq!(day.get_first_solution(), "2");
    }

    #[test]
    fn _14() {
        let day = Day1::new("14".to_string());
        assert_eq!(day.get_first_solution(), "2");
    }

    #[test]
    fn _1969() {
        let day = Day1::new("1969".to_string());
        assert_eq!(day.get_first_solution(), "654");
    }

    #[test]
    fn _100756() {
        let day = Day1::new("100756".to_string());
        assert_eq!(day.get_first_solution(), "33583");
    }
}

#[cfg(test)]
mod part_two {
    use super::*;

    #[test]
    fn _12() {
        let day = Day1::new("12".to_string());
        assert_eq!(day.get_second_solution(), "2");
    }

    #[test]
    fn _14() {
        let day = Day1::new("1969".to_string());
        assert_eq!(day.get_second_solution(), "966");
    }

    #[test]
    fn _100756() {
        let day = Day1::new("100756".to_string());
        assert_eq!(day.get_second_solution(), "50346");
    }
}
