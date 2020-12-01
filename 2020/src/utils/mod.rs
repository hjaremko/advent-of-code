use clap::App;
use aoc_fetch::AocInput;

pub trait Day {
    fn new(input: AocInput) -> Self;
    fn get_first_solution(&self) -> String;
    fn get_second_solution(&self) -> String;
}

pub fn get_day_year() -> (String, String) {
    let yaml = load_yaml!("../cli.yml");
    let matches = App::from_yaml(yaml).get_matches();
    let day = matches.value_of("day").unwrap().to_string();
    let year = matches.value_of("year").unwrap_or("2020").to_string();

    (day, year)
}

macro_rules! measure {
    ($self:ident, $f:ident) => {{
        let timer = SystemTime::now();
        let duration = SystemTime::now().duration_since(timer).unwrap();
        let result = $self.$f();
        let took = format!("{}.{:09}s", duration.as_secs(), duration.subsec_nanos());
        (result, took)
    }};
}

macro_rules! solve {
    ($day:expr, $input:expr) => {
        println!("⋆ DAY {} ⋆", $day);
        paste::expr! {
            let day = days::[<day $day>]::[<Day $day>]::new($input);
            let (answer, time) = measure!(day, get_first_solution);
            println!("PART ONE: {}, {}", time, answer);
            let (answer, time) = measure!(day, get_second_solution);
            println!("PART TWO: {}, {}", time, answer);
        }
    };
}

use ::std::io::Write;
use log::{Level, LevelFilter, Metadata, Record, SetLoggerError};
use termcolor::{Color, ColorChoice, ColorSpec, StandardStream, WriteColor};

pub struct Logger;

fn write_log(record: &Record, to_print: (Color, &str)) {
    let (color, level) = to_print;
    let mut stdout = StandardStream::stdout(ColorChoice::Always);
    stdout
        .set_color(ColorSpec::new().set_fg(Some(color)))
        .unwrap();
    write!(&mut stdout, "[{}] ", level).unwrap();
    stdout
        .set_color(ColorSpec::new().set_fg(Some(Color::White)))
        .unwrap();
    writeln!(&mut stdout, "{}", record.args()).unwrap();
}

impl log::Log for Logger {
    fn enabled(&self, _metadata: &Metadata) -> bool {
        true
    }

    fn log(&self, record: &Record) {
        if self.enabled(record.metadata()) {
            let to_print = match record.level() {
                Level::Error => (Color::Red, "error"),
                Level::Warn => (Color::Yellow, "warn"),
                Level::Info => (Color::Cyan, "info"),
                Level::Debug => (Color::Magenta, "debug"),
                Level::Trace => (Color::Blue, "trace"),
            };

            write_log(record, to_print);
        }
    }

    fn flush(&self) {}
}

static LOGGER: Logger = Logger;

pub fn init(level: LevelFilter) -> Result<(), SetLoggerError> {
    log::set_logger(&LOGGER).map(|()| log::set_max_level(level))
}
