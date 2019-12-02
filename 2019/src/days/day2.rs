use crate::utils::Day;
use crate::utils::intcode::IntcodeMachine;

pub struct Day2 {
    machine: IntcodeMachine,
}

impl Day2 {}

impl Day for Day2 {
    fn new(input: String) -> Self {
        let input: Vec<i128> = input
            .trim()
            .split(',')
            .map(|x| x.parse().ok().unwrap())
            .collect();

        Day2 {
            machine: IntcodeMachine::new(input),
        }
    }

    fn get_first_solution(&self) -> String {
        format!("{}", self.machine.execute(12, 2).get(0))
    }

    fn get_second_solution(&self) -> String {
        for noun in 0..=99 {
            for verb in 0..=99 {
                if self.machine.execute(noun, verb).get(0) == 19_690_720 {
                    return format!("{}", noun * 100 + verb);
                }
            }
        }

        "".to_string()
    }
}
