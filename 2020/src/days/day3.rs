use crate::utils::Day;
use aoc_fetch::AocInput;
// use log::debug;

pub struct Day3 {
    input: AocInput,
}

impl Day for Day3 {
    fn new(input: AocInput) -> Self {
        Day3 { input }
    }

    fn get_first_solution(&self) -> String {
        self.traverse(3, 1).to_string()
    }

    fn get_second_solution(&self) -> String {
        let tree_counts = vec![
            self.traverse(1, 1),
            self.traverse(3, 1),
            self.traverse(5, 1),
            self.traverse(7, 1),
            self.traverse(1, 2),
        ];

        tree_counts.iter().product::<usize>().to_string()
    }
}

struct Step {
    current: usize,
    step: usize,
}

impl Step {
    fn new(step: usize) -> Self {
        Step {
            current: step,
            step,
        }
    }

    fn next(&mut self) -> usize {
        let save = self.current % 31;
        self.current += self.step;
        save
    }
}

impl Day3 {
    fn traverse(&self, right: usize, down: usize) -> usize {
        let lines: Vec<&str> = self.input.input.lines().collect();
        let mut step = Step::new(right);

        (down..lines.len())
            .step_by(down)
            .map(|i| lines[i].chars().nth(step.next()).unwrap())
            .filter(|c| *c == '#')
            .count()
    }
}
