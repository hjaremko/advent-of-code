use crate::utils::Day;
use aoc_fetch::AocInput;

pub struct Day2 {
    values: Vec<Pass>,
}

struct Pass {
    content: String,
    policy_letter: char,
    low: usize,
    high: usize,
}

impl Day for Day2 {
    fn new(input: AocInput) -> Self {
        Day2 {
            values: input
                .input
                .lines()
                .map(|line| {
                    let slitted: Vec<&str> = line.split_ascii_whitespace().collect();
                    let lh: Vec<&str> = slitted[0].split("-").collect();

                    Pass {
                        content: slitted[2].to_string(),
                        policy_letter: slitted[1].chars().next().unwrap(),
                        low: lh[0].parse().ok().unwrap(),
                        high: lh[1].parse().ok().unwrap(),
                    }
                })
                .collect(),
        }
    }

    fn get_first_solution(&self) -> String {
        self.values
            .iter()
            .filter(|pass| {
                let matching = pass
                    .content
                    .chars()
                    .filter(|a| *a == pass.policy_letter)
                    .count();
                matching >= pass.low && matching <= pass.high
            })
            .count()
            .to_string()
    }

    fn get_second_solution(&self) -> String {
        let check_policy = |pass: &Pass, index: usize| {
            pass.content.chars().nth(index - 1).unwrap() == pass.policy_letter
        };

        self.values
            .iter()
            .filter(|pass| {
                let low_match = check_policy(pass, pass.low);
                let high_match = check_policy(pass, pass.high);

                low_match ^ high_match
            })
            .count()
            .to_string()
    }
}
