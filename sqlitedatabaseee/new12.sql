-- ============================================
-- WORDQUEST DATABASE SCHEMA
-- Created for SQLite (VS Code compatible)
-- ============================================

-- Drop old tables to avoid duplicate errors
DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS sections;
DROP TABLE IF EXISTS words;
DROP TABLE IF EXISTS riddles;
DROP TABLE IF EXISTS progress;
DROP TABLE IF EXISTS stats;

-- ============================================
-- USERS TABLE
-- Stores player profile and XP data
-- ============================================
CREATE TABLE users (
    userid INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    level INTEGER DEFAULT 1,
    xp INTEGER DEFAULT 0,
    total_words_learned INTEGER DEFAULT 0
);

-- ============================================
-- SECTIONS TABLE
-- Each section groups words by difficulty or theme
-- ============================================
CREATE TABLE sections (
    sectionid INTEGER PRIMARY KEY AUTOINCREMENT,
    section_name TEXT NOT NULL,
    difficulty TEXT CHECK(difficulty IN ('Beginner', 'Intermediate', 'Advanced', 'Expert')) NOT NULL
);

-- ============================================
-- WORDS TABLE
-- Stores all vocabulary words with meaning + example
-- ============================================
CREATE TABLE words (
    wordid INTEGER PRIMARY KEY AUTOINCREMENT,
    word TEXT NOT NULL UNIQUE,
    meaning TEXT NOT NULL,
    example_sentence TEXT,
    sectionid INTEGER,
    FOREIGN KEY (sectionid) REFERENCES sections(sectionid)
);

-- ============================================
-- RIDDLES TABLE
-- Each riddle has a question, answer, and XP reward
-- ============================================
CREATE TABLE riddles (
    riddleid INTEGER PRIMARY KEY AUTOINCREMENT,
    question TEXT NOT NULL,
    answer TEXT NOT NULL,
    xp_reward INTEGER DEFAULT 20
);

-- ============================================
-- PROGRESS TABLE
-- Tracks which words/riddles each user has completed
-- ============================================
CREATE TABLE progress (
    progressid INTEGER PRIMARY KEY AUTOINCREMENT,
    userid INTEGER NOT NULL,
    wordid INTEGER,
    riddleid INTEGER,
    completed INTEGER DEFAULT 0,
    FOREIGN KEY (userid) REFERENCES users(userid),
    FOREIGN KEY (wordid) REFERENCES words(wordid),
    FOREIGN KEY (riddleid) REFERENCES riddles(riddleid)
);

-- ============================================
-- STATS TABLE (Optional)
-- Tracks user activity for analytics
-- ============================================
CREATE TABLE stats (
    statid INTEGER PRIMARY KEY AUTOINCREMENT,
    userid INTEGER NOT NULL,
    total_quizzes INTEGER DEFAULT 0,
    total_riddles_solved INTEGER DEFAULT 0,
    last_login DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (userid) REFERENCES users(userid)
);

-- ============================================
-- INITIAL DATA
-- ============================================

-- Insert some demo users
INSERT INTO users (username) VALUES ('Player1'), ('Player2');

-- Insert example sections
INSERT INTO sections (section_name, difficulty)
VALUES ('Mythic Vocabulary', 'Advanced'),
       ('Academic Words', 'Intermediate'),
       ('Daily English', 'Beginner');

-- Insert a few sample words
INSERT INTO words (word, meaning, example_sentence, sectionid)
VALUES 
('Ephemeral', 'Lasting for a very short time', 'Beauty is ephemeral, but art endures.', 1),
('Cogent', 'Clear, logical, and convincing', 'She presented a cogent argument.', 2),
('Serendipity', 'The occurrence of events by chance in a happy way', 'Meeting her was pure serendipity.', 3);

-- Insert sample riddles
INSERT INTO riddles (question, answer, xp_reward)
VALUES 
('I speak without a mouth and hear without ears. What am I?', 'Echo', 30),
('What has keys but can’t open locks?', 'Piano', 15);

-- Done ✅
