use std::sync::atomic::{AtomicBool, AtomicU64, Ordering};
use std::sync::Arc;
use std::time::{Duration, Instant, SystemTime, UNIX_EPOCH};
use std::thread;
use tauri::{Emitter, Manager};
use rdev::{listen, Event, EventType};

// --- STRUKTURA ZARZĄDZAJĄCA STANEM ---
// Używamy atomowych typów, żeby nie bawić się w ciągłe .lock().unwrap()
struct AppTimer {
    running: AtomicBool,
    duration_secs: AtomicU64,
    // Przechowujemy czas ostatniej aktywności jako timestamp (u64)
    last_activity: AtomicU64, 
}

impl AppTimer {
    fn new() -> Self {
        Self {
            running: AtomicBool::new(false),
            duration_secs: AtomicU64::new(0),
            last_activity: AtomicU64::new(get_current_timestamp()),
        }
    }

    fn reset_timer(&self) {
        // To jest thread-safe bez mutexów!
        self.last_activity.store(get_current_timestamp(), Ordering::Relaxed);
    }

    fn start(&self, seconds: u64) {
        self.duration_secs.store(seconds, Ordering::Relaxed);
        self.reset_timer();
        self.running.store(true, Ordering::Relaxed);
    }

    fn stop(&self) {
        self.running.store(false, Ordering::Relaxed);
    }
}

// Pomocnicza funkcja do pobierania czasu jako liczby
fn get_current_timestamp() -> u64 {
    SystemTime::now().duration_since(UNIX_EPOCH).unwrap().as_secs()
}

#[tauri::command]
fn greet(name: &str) -> String {
    format!("Hello, {}! You've been greeted from Rust!", name)
}

#[tauri::command]
fn start_timer(seconds: u64, state: tauri::State<Arc<AppTimer>>) {
    println!("[RUST] Starting timer for {} seconds", seconds);
    //state.start(seconds);
}

#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    let timer_state = Arc::new(AppTimer::new());

    let monitor_state = timer_state.clone();

    tauri::Builder::default()
        .plugin(tauri_plugin_opener::init())
        .manage(timer_state.clone())
        .invoke_handler(tauri::generate_handler![greet, start_timer])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
