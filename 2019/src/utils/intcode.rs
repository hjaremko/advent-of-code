#[derive(Clone)]
pub struct IntcodeMachine {
    memory: Vec<i128>,
}

impl IntcodeMachine {
    pub fn new(input: Vec<i128>) -> Self {
        IntcodeMachine { memory: input }
    }

    pub fn get(&self, index: usize) -> i128 {
        self.memory[index]
    }

    pub fn execute_mut(&mut self, noun: i128, verb: i128) {
        self.memory[1] = noun;
        self.memory[2] = verb;
        let mut instruction_pointer = 0;

        loop {
            instruction_pointer += match self.memory[instruction_pointer] {
                1 => self.add(instruction_pointer),
                2 => self.mult(instruction_pointer),
                99 => {
                    break;
                }
                _ => {
                    panic!("Something went wrong");
                }
            };
        }
    }

    pub fn execute(&self, noun: i128, verb: i128) -> Self {
        let mut machine = self.clone();
        machine.execute_mut(noun, verb);
        machine
    }

    fn add(&mut self, pointer: usize) -> usize {
        let f = self.memory[self.memory[pointer + 1] as usize];
        let s = self.memory[self.memory[pointer + 2] as usize];
        let dest = self.memory[pointer + 3] as usize;

        self.memory[dest] = (f + s) as i128;

        4
    }

    fn mult(&mut self, pointer: usize) -> usize {
        let f = self.memory[self.memory[pointer + 1] as usize];
        let s = self.memory[self.memory[pointer + 2] as usize];
        let dest = self.memory[pointer + 3] as usize;

        self.memory[dest] = (f * s) as i128;

        4
    }
}
