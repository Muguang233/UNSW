import { listObjections, Objection, ExaminationType } from './objection';

test('Remove this test and uncomment the tests below', () => {
  expect(1 + 1).toBe(2);
});

test('error cases', () => {
  expect(
    () => listObjections('', 'yes', ExaminationType.CROSS)
  ).toThrow(Error);
  expect(
    () => listObjections('I am what?', '', ExaminationType.CROSS)
  ).toThrow(Error);
});

describe('argumentative cases', () => {
  test.each([
    {
      question: 'You are totally lying!',
      testimony: 'No you!',
      type: ExaminationType.CROSS,
      objections: new Set([Objection.ARGUMENTATIVE]),
    },
    {
      question: 'This is direct, yes!',
      testimony: 'Yes, so not argumentative!',
      type: ExaminationType.DIRECT,
      objections: new Set([]),
    },
  ])('$objections', ({ question, testimony, type, objections }) => {
    expect(listObjections(question, testimony, type)).toEqual(objections);
  });
});

test('COMPOUND cases', () => {
  expect(
    listObjections('I am ??', 'I am testimony', ExaminationType.CROSS)
  ).toEqual(new Set([Objection.COMPOUND]));
});
test('HEARSAY cases', () => {
  expect(
    listObjections('I am ?', 'I am heard from', ExaminationType.CROSS)
  ).toEqual(new Set([Objection.HEARSAY]));
  expect(
    listObjections('I am ?', 'I am told me', ExaminationType.CROSS)
  ).toEqual(new Set([Objection.HEARSAY]));
});

test.each([
  {
    question: 'why did you do that?',
    testimony: 'do you',
  },
  {
    question: 'do you agree with that?',
    testimony: 'do I',
  },
  {
    question: 'are you right?',
    testimony: 'do you',
  },
  {
    question: 'are you correct?',
    testimony: 'do you',
  },
])('LEADING cases', ({ question, testimony }) => {
  expect(
    listObjections(question, testimony, ExaminationType.DIRECT)
  ).toEqual(new Set([Objection.LEADING]));
});

test('NON_RESPONSIVE cases', () => {
  expect(
    listObjections('we are different?', 'yes', ExaminationType.CROSS)
  ).toEqual(new Set([Objection.NON_RESPONSIVE]));
});

test('RELEVANCE cases', () => {
  expect(
    listObjections('Yes?', 'this is a very long testimony yes', ExaminationType.CROSS)
  ).toEqual(new Set([Objection.RELEVANCE]));
});

test('SPECULATION cases', () => {
  expect(
    listObjections('I am question?', 'I need to think', ExaminationType.DIRECT)
  ).toEqual(new Set([Objection.SPECULATION]));
  expect(
    listObjections('I might have to think?', 'I am testimony', ExaminationType.CROSS)
  ).toEqual(new Set([Objection.SPECULATION]));
});
