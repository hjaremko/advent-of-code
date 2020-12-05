use crate::utils::Day;
use aoc_fetch::AocInput;
use itertools::Itertools;
// use log::debug;

pub struct Day5 {
    ids: Vec<i32>,
}

impl Day for Day5 {
    fn new(input: AocInput) -> Self {
        Day5 {
            ids: input
                .split()
                .iter()
                .map(|str| Day5::calc_id(str))
                .sorted()
                .collect(),
        }
    }

    fn get_first_solution(&self) -> String {
        self.ids.last().unwrap().to_string()
    }

    fn get_second_solution(&self) -> String {
        let low = *self.ids.first().unwrap();
        let high = *self.ids.last().unwrap();

        for i in low..high {
            if !self.ids.contains(&i) {
                return i.to_string();
            }
        }

        "".to_string()
    }
}

impl Day5 {
    fn calc_id(str: &String) -> i32 {
        let row = Day5::convert(&str[0..7], 'F');
        let col = Day5::convert(&str[7..10], 'L');

        row * 8 + col
    }

    fn convert(str: &str, cc: char) -> i32 {
        let bin: String = str
            .chars()
            .map(|c| if c == cc { '0' } else { '1' })
            .collect();

        isize::from_str_radix(&bin, 2).unwrap() as i32
    }
}

#[cfg(test)]
mod sample_tests {
    use super::*;

    const RAW_TEST_INPUT: &str = r#"BBFFBBFRLL"#;

    #[test]
    fn part_one_test() {
        let test_input: AocInput = AocInput::new(
            "5".to_string(),
            "2020".to_string(),
            RAW_TEST_INPUT.to_string(),
        );

        let day = Day5::new(test_input);
        assert_eq!(day.get_first_solution(), "820");
    }
}
