use crate::utils::Day;
use aoc_fetch::AocInput;
use itertools::Itertools;
use std::collections::HashSet;
// use log::debug;

pub struct Day6 {
    input: Vec<Group>,
}

impl Day for Day6 {
    fn new(input: AocInput) -> Self {
        Day6 {
            input: input
                .split_by::<String>("\n\n")
                .iter()
                .map(|g| Group {
                    qs: g.split_whitespace().map(|x| x.to_string()).collect(),
                })
                .collect(),
        }
    }

    fn get_first_solution(&self) -> String {
        self.input
            .iter()
            .map(|g| g.qs.iter().flat_map(|s| s.chars()).unique().count())
            .sum::<usize>()
            .to_string()
    }

    fn get_second_solution(&self) -> String {
        self.input
            .iter()
            .map(|g| {
                let hs: Vec<HashSet<char>> =
                    g.qs.iter()
                        .map(|x| x.chars().collect::<HashSet<char>>())
                        .collect();

                let f: HashSet<char> = hs[0].iter().cloned().collect();

                hs.iter()
                    .skip(1)
                    .fold(f, |acc, f| acc.intersection(f).cloned().collect())
                    .len()
            })
            .sum::<usize>()
            .to_string()
    }
}

#[derive(Debug)]
struct Group {
    qs: Vec<String>,
}
