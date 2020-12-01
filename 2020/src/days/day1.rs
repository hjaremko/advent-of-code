use crate::utils::Day;
use aoc_fetch::AocInput;
use std::collections::HashSet;

pub struct Day1 {
    values: Vec<i32>,
}

impl Day for Day1 {
    fn new(input: AocInput) -> Self {
        Day1 {
            values: input.split(),
        }
    }

    fn get_first_solution(&self) -> String {
        let books: HashSet<i32> = self.values.iter().cloned().collect();

        for a in &self.values {
            let b = 2020 - a;

            if books.contains(&b) {
                return (a * books.get(&b).unwrap()).to_string();
            }
        }

        "none".to_string()
    }

    fn get_second_solution(&self) -> String {
        let books: HashSet<i32> = self.values.iter().cloned().collect();

        for a in &self.values {
            for b in &self.values {
                let c = 2020 - a - b;

                if books.contains(&c) {
                    return (a * b * books.get(&c).unwrap()).to_string();
                }
            }
        }

        "none".to_string()
    }
}

#[cfg(test)]
mod sample_tests {
    use super::*;

    const RAW_TEST_INPUT: &str = r#"1721
979
366
299
675
1456"#;

    #[test]
    fn part_one_test() {
        let test_input: AocInput = AocInput::new(
            "1".to_string(),
            "2020".to_string(),
            RAW_TEST_INPUT.to_string(),
        );

        let day = Day1::new(test_input);
        assert_eq!(day.get_first_solution(), "514579");
    }

    #[test]
    fn part_two_test() {
        let test_input: AocInput = AocInput::new(
            "1".to_string(),
            "2020".to_string(),
            RAW_TEST_INPUT.to_string(),
        );

        let day = Day1::new(test_input);
        assert_eq!(day.get_second_solution(), "241861950");
    }
}
